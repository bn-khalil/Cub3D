#include <stdio.h>
#include <mlx.h>

int main() {
    void *mlx;
    void *mlx_w;
    char map[20][21] = {
        "11111111111111111111",
        "10000000001100000001",
        "10111100001101111101",
        "10100000100001000101",
        "10101110000000000101",
        "10100010000000000101",
        "10111011101111110101",
        "10001000000000000101",
        "10101111100000000101",
        "10101111100000000101",
        "10110000101111110101",
        "10000000101000000101",
        "11110111001011111111",
        "10010111001000000101",
        "10110110001011011101",
        "10000111001011000101",
        "11111111000011111111",
        "10000000000000000001",
        "10111111111111111001",
        "11111111111111111111"
    };

    int hight = 20;
    int with = 20;
    int size_pix = 35;

    mlx = mlx_init();
    mlx_w = mlx_new_window(mlx, with * size_pix, hight * size_pix, "cub3d");
    mlx_new_image(mlx, 100, 100);

    int i = 0;
    int j;
    int x;
    int y;
    while (i < 20)
    {
        j = 0;
        while (j < 21)
        {
            y = 0;
            if (map[i][j] == '1') {
                while (y < size_pix -1 )
                {
                    x = 0;
                    while (x < size_pix - 1)
                    {
                        mlx_pixel_put(mlx, mlx_w, j * size_pix + x, i * size_pix + y, 0xfff);
                        x++;
                    }
                    y++;
                }
            }
            j++;
        }
        i++;
    }
    mlx_loop(mlx);
    return 0;
}