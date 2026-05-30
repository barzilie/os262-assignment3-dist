#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define SCREEN_W 640
#define SCREEN_H 480

// Framebuffer total bytes and number of 4 KB pages required
#define FB_BYTES (SCREEN_W * SCREEN_H * 4)

int main(int argc, char *argv[])
{

    uint32 *buf[2];
    buf[0] = (uint32 *)sbrk(FB_BYTES);
    buf[1] = (uint32 *)sbrk(FB_BYTES);
    for (int i = 0; i < FB_BYTES / 4; i++)
    {
        buf[0][i] = 0x00FF0000; // Red (order is Blue Green Red X)
        buf[1][i] = 0x000000FF; // Blue
    }
    for (int i = 0; i < 50; i++)
    {
        flip_display(buf[i & 1]); // display now reads buf[i & 1]
        sleep(3);
    }
    return 0;
}