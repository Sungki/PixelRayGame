#pragma once

#include <windows.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define PIXEL_COLOR_CHANNELS b, g, r, a

typedef unsigned int uint;
typedef uint8_t   u8;
typedef int8_t    i8;
typedef uint16_t  u16;
typedef int16_t   i16;
typedef uint32_t  u32;
typedef int32_t   i32;
typedef uint64_t  u64;
typedef int64_t   i64;
typedef float     f32;
typedef double    f64;
typedef u32       b32;
typedef size_t    usize;
typedef ptrdiff_t isize;

#define unused(x) (void)x

#define align_to(value, N) ((value + (N-1)) & ~(N-1))
#define ceil_div(n, a) (((n) + (a-1))/(a))
#define equalf(a, b, epsilon) (fabs(b - a) <= epsilon)

#define maximum(a, b) ((a) > (b) ? (a) : (b))
#define minimum(a, b) ((a) < (b) ? (a) : (b))
#define clamp(x, a, b)  (maximum(a, minimum(x, b)))
#define array_count(a) (sizeof(a) / sizeof((a)[0]))
#define swap_t(T, a, b) do { T tmp__ = a; a = b; b = tmp__; } while (0)

#define lerp(v0, v1, t) ((1-(t))*(v0) + (t)*(v1))

#define kilobytes(n) (1024*(n))
#define megabytes(n) (1024*kilobytes(n))
#define gigabytes(n) (1024*megabytes(n))

#define PUNITY_STACK_CAPACITY megabytes(16)
#define PUNITY_STORAGE_CAPACITY megabytes(16)

extern int init();
extern void step();

typedef struct {
    u8* begin;
    u8* end;
    u8* it;
    u8* cap;
} Bank;

void* bank_push(Bank* bank, u32 size);

#define bank_push_t(Bank, Type, Count) \
    ((Type*)bank_push(Bank, (Count) * sizeof(Type)))

typedef union {
    struct {
        u8 PIXEL_COLOR_CHANNELS;
    };
    u32 rgba;
} Color;

extern inline Color color_make(u8 r, u8 g, u8 b, u8 a);

Color color_make(u8 r, u8 g, u8 b, u8 a)
{
    Color c;
    c.r = r;
    c.g = g;
    c.b = b;
    c.a = a;
    return c;
}

typedef struct {
    int begin;
    int end;
    int it;
} PaletteRange;

typedef struct {
    Color colors[256];
    PaletteRange ranges[16];
    int ranges_count;
} Palette;

typedef struct {
    i32 width;
    i32 height;
    i32 pitch;
    u8* pixels;
    i32 palette_range;
} Bitmap;

typedef struct {
    Bitmap* bitmap;
    i32 translate_x;
    i32 translate_y;
} Canvas;

typedef struct Window_ {
    int width;
    int height;
    f32 scale;

    f32 viewport_min_x;
    f32 viewport_min_y;
    f32 viewport_max_x;
    f32 viewport_max_y;

    u8* buffer;
} Window;

typedef struct {
    Bank* stack;        //4
    Bank* storage;
    Window window;      //12
    Canvas canvas;      //12
    Palette* palette;   //4
} Core;

extern Core* CORE;
Core* CORE = 0;

void palette_init(Palette* palette)
{
    memset(palette, 0, sizeof(Palette));

    palette->ranges[0].begin = 1;
    palette->ranges[0].end = 0xFF;
    palette->ranges[0].it = 1;
    palette->ranges_count = 1;
}

u8 palette_color_set(Palette* palette, u8 index, Color color)
{
    palette->colors[index] = color;
    return index;
}

int bitmap_init_(Bitmap* bitmap, void* pixels, int type, const char* path)
{
    if (!pixels) {
        return 1;
    }

    u32 size = bitmap->width * bitmap->height;
    memcpy(bitmap->pixels, pixels, size);

    return 1;
}

void bitmap_init_ex_(Bank* bank, Bitmap* bitmap, i32 width, i32 height, void* pixels, int bpp, int palette_range, const char* path)
{
    bitmap->width = width;
    bitmap->pitch = align_to(width, 16);
    bitmap->height = height;
    bitmap->palette_range = palette_range;

    bitmap->pixels = (u8*)bank_push(bank, 4);
    u32 size = bitmap->pitch * height;
    bitmap->pixels = (u8*)bank_push(bank, size);
    bitmap_init_(bitmap, pixels, bpp, path);
}

void bitmap_init(Bitmap* bitmap, i32 width, i32 height, void* pixels, int bpp, int palette_range)
{
    bitmap_init_ex_(CORE->storage, bitmap, width, height, pixels, bpp, palette_range, 0);
}

void bitmap_clear(Bitmap* bitmap, u8 color)
{
    memset(bitmap->pixels, color, bitmap->width * bitmap->height);
}

void canvas_clear(u8 color)
{
    memset(CORE->canvas.bitmap->pixels, color, CORE->canvas.bitmap->width * CORE->canvas.bitmap->height);
}

void pixel_draw(i32 x, i32 y, u8 color)
{
    *(CORE->canvas.bitmap->pixels + x + (y * CORE->canvas.bitmap->width)) = color;
}

void* virtual_reserve(void* ptr, u32 size)
{
    ptr = VirtualAlloc(ptr, size, MEM_RESERVE, PAGE_NOACCESS);
    return ptr;
}

void* virtual_commit(void* ptr, u32 size)
{
    ptr = VirtualAlloc(ptr, size, MEM_COMMIT, PAGE_READWRITE);
    return ptr;
}

void bank_init(Bank* bank, u32 capacity)
{
    bank->begin = bank->it = bank->end = (u8*)virtual_reserve(0, capacity);
    bank->cap = bank->begin + capacity;
}

void* bank_push(Bank* stack, u32 size)
{
    void* ptr;

    if ((stack->end - stack->it) < size) {
        if ((stack->cap - stack->it) < size) {
            printf("Not enought memory in bank (%d required, %d available).\n", (int)(stack->end - stack->it), size);
            return 0;
        }
        else {
            u32 additional_size = size - (stack->end - stack->it);
            additional_size = minimum((stack->cap - stack->it), align_to(additional_size, 4096));
            ptr = virtual_commit(stack->end, additional_size);
            stack->end += additional_size;
        }
    }
    ptr = stack->it;
    stack->it += size;
    return ptr;
}

int punity_init(const char* args)
{
    if (AttachConsole(ATTACH_PARENT_PROCESS) || AllocConsole()) {
        freopen("CONOUT$", "w", stdout);
        freopen("CONOUT$", "w", stderr);
    }

    static Bank s_stack = { 0 };
    static Bank s_storage = { 0 };

    static Core s_core = { 0 };
    CORE = &s_core;
    memset(CORE, 0, sizeof(Core));

    static Palette s_palette;
    CORE->palette = &s_palette;
    palette_init(CORE->palette);
    palette_color_set(CORE->palette, 0, color_make(0x00, 0x00, 0x00, 0x00));
    palette_color_set(CORE->palette, 1, color_make(0x00, 0x00, 0x00, 0xFF));
    palette_color_set(CORE->palette, 2, color_make(0xFF, 0xFF, 0xFF, 0xFF));
    palette_color_set(CORE->palette, 3, color_make(0x00, 0xff, 0x00, 0xff));

    CORE->window.width = 320;
    CORE->window.height = 200;
    CORE->window.scale = 3;

    CORE->stack = &s_stack;
    CORE->storage = &s_storage;

    bank_init(CORE->stack, PUNITY_STACK_CAPACITY);
    bank_init(CORE->storage, PUNITY_STORAGE_CAPACITY);

    static Bitmap s_canvas_bitmap = { 0 };
    CORE->canvas.bitmap = &s_canvas_bitmap;
    bitmap_init(CORE->canvas.bitmap, CORE->window.width, CORE->window.height, 0, 0, 0);
    bitmap_clear(CORE->canvas.bitmap, 255);
    CORE->window.buffer = CORE->canvas.bitmap->pixels;

    if (!init()) {
        return 1;
    }

    return 0;
}

void punity_frame_step()
{
    step();
}

static struct
{
    HINSTANCE instance;
    HCURSOR cursor;
    HWND window;
    u32* window_buffer;
} win32_ = { 0 };

#define WIN32_DEFAULT_STYLE_ (WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX)

static LRESULT CALLBACK win32_window_callback_(HWND window, UINT message, WPARAM wp, LPARAM lp)
{
    switch (message)
    {
    case WM_CLOSE:
        PostQuitMessage(0);
        break;

    case WM_SIZE:
    {
        f32 width = (UINT)(lp & 0xffff);
        f32 height = (UINT)(lp >> 16) & 0xffff;

        f32 scale_x = width / (f32)CORE->window.width;
        f32 scale_y = height / (f32)CORE->window.height;

        CORE->window.scale = minimum(scale_x, scale_y);

        f32 viewport_width = CORE->window.width * CORE->window.scale;
        f32 viewport_height = CORE->window.height * CORE->window.scale;

        CORE->window.viewport_min_x = (width - viewport_width) / 2;
        CORE->window.viewport_min_y = (height - viewport_height) / 2;
        CORE->window.viewport_max_x = CORE->window.viewport_min_x + viewport_width;
        CORE->window.viewport_max_y = CORE->window.viewport_min_y + viewport_height;
        return 0;
    }
    break;

    }

    return DefWindowProcA(window, message, wp, lp);
}

int CALLBACK WinMain(HINSTANCE instance, HINSTANCE prev_instance, LPSTR command_line, int show_code)
{
    win32_.cursor = LoadCursor(0, IDC_ARROW);
    win32_.instance = instance;

    punity_init(command_line);

    WNDCLASSA window_class = { 0 };
    window_class.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    window_class.lpfnWndProc = win32_window_callback_;
    window_class.hInstance = win32_.instance;
    window_class.hIcon = LoadIcon(win32_.instance, IDI_APPLICATION);
    window_class.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    window_class.lpszClassName = "Punity";

    if (!RegisterClassA(&window_class)) {
        printf("RegisterClassA failed.\n");
        return 1;
    }

    RECT rc;
    int screen_width = GetSystemMetrics(SM_CXSCREEN);
    int screen_height = GetSystemMetrics(SM_CYSCREEN);
    int window_width = CORE->window.width * CORE->window.scale;
    int window_height = CORE->window.height * CORE->window.scale;
    rc.left = (screen_width - (window_width)) / 2;
    rc.top = (screen_height - (window_height)) / 2;
    rc.right = rc.left + window_width;
    rc.bottom = rc.top + window_height;

    win32_.window = CreateWindowExA(
        0,
        window_class.lpszClassName,
        "SimpleWindow",
        WIN32_DEFAULT_STYLE_,
        rc.left, rc.top,
        rc.right - rc.left, rc.bottom - rc.top,
        0, 0,
        win32_.instance,
        0);

    if (!win32_.window) {
        printf("CreateWindowExA failed.\n");
        return 1;
    }

    BITMAPINFO window_bmi;
    memset(&window_bmi, 0, sizeof(BITMAPINFO));
    window_bmi.bmiHeader.biSize = sizeof(window_bmi.bmiHeader);
    window_bmi.bmiHeader.biWidth = CORE->window.width;
    window_bmi.bmiHeader.biHeight = CORE->window.height;
    window_bmi.bmiHeader.biPlanes = 1;
    window_bmi.bmiHeader.biBitCount = 32;
    window_bmi.bmiHeader.biCompression = BI_RGB;

    u32* window_buffer = 0;
    window_buffer = (u32*)bank_push(CORE->stack, (CORE->window.width * 4) * CORE->window.height);

    ShowCursor(TRUE);
    ShowWindow(win32_.window, SW_SHOW);

    int x, y;
    u32* window_row;
    u8* canvas_it;
    MSG message;

    while (1)
    {
        while (PeekMessage(&message, 0, 0, 0, PM_REMOVE))
        {
            if (message.message == WM_QUIT) {
                goto end;
            }
            TranslateMessage(&message);
            DispatchMessageA(&message);
        }

        punity_frame_step();

        window_row = window_buffer;
        canvas_it = CORE->window.buffer;
        for (y = CORE->window.height; y != 0; --y) {
            window_row = window_buffer + ((y - 1) * CORE->window.width);
            for (x = 0; x != CORE->window.width; ++x) {
                *(window_row++) = CORE->palette->colors[*canvas_it++].rgba;
            }
        }

        HDC dc = GetDC(win32_.window);
        StretchDIBits(dc,
            CORE->window.viewport_min_x,
            CORE->window.viewport_min_y,
            CORE->window.viewport_max_x - CORE->window.viewport_min_x,
            CORE->window.viewport_max_y - CORE->window.viewport_min_y,
            0, 0, CORE->window.width, CORE->window.height,
            window_buffer,
            &window_bmi,
            DIB_RGB_COLORS,
            SRCCOPY);
        ReleaseDC(win32_.window, dc);
    }

end:;

    return 0;
}