#include <stdio.h>
#include <libc.h>
#include <mlx.h>

#define LEFT 0
#define DOWN 1
#define RIGHT 2
#define UP 13
#define SIZE 35

#define pi = 3.14159265359

typedef struct s_plyer{
    int x;
    int y;
    int up;
    int down;
    int left;
    int right;
} t_plyer;

typedef struct s_data{
    void *mxl;
    void *win;
    void *img;
    char *address;
    char **map;
    int bits_per_pixel;
    int line_lenght;
    int endian;
    t_plyer plr;
} t_data;

char **get_map(void)
{
    static const char raw_map[20][21] = {
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

    char **map = malloc(sizeof(char *) * 21); // 20 rows + NULL
    if (!map)
        return NULL;

    for (int i = 0; i < 20; i++)
    {
        map[i] = malloc(21); // each row has 20 chars + null terminator
        if (!map[i])
        {
            while (--i >= 0)
                free(map[i]);
            free(map);
            return NULL;
        }
        strcpy(map[i], raw_map[i]);
    }
    map[20] = NULL; // optional NULL terminator
    return map;
}


int	key_enter(int keycode, t_plyer *plr)
{
    printf(" %d \n", keycode);
	if (keycode == 0)
		plr->left = 1;
	else if (keycode == 1)
		plr->down = 1;
	else if (keycode == 2)
		plr->right = 1;
	else if (keycode == 13)
		plr->up = 1;
	return (0);
}

int	key_back(int keycode, t_plyer *plr)
{
	if (keycode == 0)
		plr->left = 0;
	else if (keycode == 1)
		plr->down = 0;
	else if (keycode == 2)
		plr->right = 0;
	else if (keycode == 13)
		plr->up = 0;
	return (0);
}


void	move_player(t_plyer *plr)
{
    int speed = 3;

	if (plr->left)
		plr->x -= speed;
	if (plr->down)
		plr->y += speed;
	if (plr->right)
		plr->x += speed;
	if (plr->up)
		plr->y -= speed;
}

void put_pxl(int x, int y, int color, t_data *data)
{
    int pos;

    pos = y * data->line_lenght + x * data->bits_per_pixel / 8;
    data->address[pos] = color & 0xFF;
    data->address[pos + 1] = (color >> 8) & 0xFF;
    data->address[pos + 2] = (color >> 16) & 0xFF;
}

void draw_square(int x, int y, int size, int color, t_data *data)
{
    int i = 0;
    while (i < size)
    {
        put_pxl(x + i, y, color, data);
        i++;
    }
    i = 0;
    while (i < size)
    {
        put_pxl(x, y + i, color, data);
        i++;
    }
    i = 0;
    while (i < size)
    {
        put_pxl(x + size - 1, y + i, color, data);
        i++;
    }
    i = 0;
    while (i < size)
    {
        put_pxl(x + i, y + size - 1, color, data);
        i++;
    }
}

void draw_m(int x, int y, int size, int color, t_data *data)
{
    int i = 0;
    int j;
    while (i < size)
    {
        j = 0;
        while (j < size)
        {
            put_pxl(x + i, y + j, color, data);
            j++;
        }
        i++;
    }
}

void redraw(t_data *data)
{
    int x;
    int y;

    x = 0;
    while (x < 20 * 35)
    {
        y = 0;
        while (y < 20 * 35)
        {
            put_pxl(y, x, 0x000000, data);
            y++;
        }
        x++;
    }
}

void draw_map(t_data *data)
{
    char **map = data->map;
    int color = 0xFFF;
    int i = 0;
    int j;
    int x;
    int y;
    while (i < 20)
    {
        j = 0;
        while (j < 21)
        {
            if (map[i][j] == '1')
                draw_m(i * 35, j * 35, 35,color, data);
            j++;
        }
        i++;
    }
}

int draw_player(t_data *data)
{
    t_plyer *p = &data->plr;
    move_player(p);
    redraw(data);
    draw_square(p->x, p->y, 10, 0xFFFFFF, data);
    draw_map(data);
    mlx_put_image_to_window(data->mxl, data->win, data->img, 0, 0);
    return (0);
}

int main() {
    t_data data;
    int hight = 20;
    int with = 20;
    data.map = get_map();
    printf("%s\n", data.map[0]);
    data.plr.x = with / 2 * SIZE;
    data.plr.y = hight / 2 * SIZE;
    data.plr.down = 0;
    data.plr.left = 0;
    data.plr.up = 0;
    data.plr.right = 0;
    data.mxl = mlx_init();
    data.win = mlx_new_window(data.mxl, with * SIZE, hight * SIZE, "cub3d");
    data.img = mlx_new_image(data.mxl, with * SIZE, hight * SIZE);
    data.address = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_lenght, &data.endian);
    mlx_put_image_to_window(data.mxl, data.win, data.img, 0, 0);
    mlx_hook(data.win, 2, 1L<<0, key_enter, &data.plr);
    mlx_hook(data.win, 3, 1L<<1, key_back, &data.plr);
    draw_square(with / 2 * SIZE, hight / 2 * SIZE, 10, 0xFFFFFF, &data);
    mlx_loop_hook(data.mxl, draw_player, &data);
    mlx_loop(data.mxl);
    return 0;
}
