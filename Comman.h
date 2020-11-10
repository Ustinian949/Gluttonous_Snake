// 初始化蛇位置数组
# define snake_length 20
enum { to_east = 2, to_west = -2, to_north = -1, to_south = 1 };
int snake_arr[snake_length][3] = { 0 };

typedef int BOOL;
# define true 1 
# define false 0 

// 边框背景数组
char back2[20][48] = { "■■■■■■■■■■■■■■■■■■■■■■■\n",
"■                                          ■\n",
"■                                          ■\n",
"■                                          ■\n",
"■                                          ■\n",
"■                                          ■\n",
"■                                          ■\n",
"■                                          ■\n",
"■                                          ■\n",
"■                                          ■\n",
"■                                          ■\n",
"■                                          ■\n",
"■                                          ■\n",
"■                                          ■\n",
"■                                          ■\n",
"■                                          ■\n",
"■                                          ■\n",
"■                                          ■\n",
"■                                          ■\n",
"■■■■■■■■■■■■■■■■■■■■■■■\n" };

// 蛇的方向
int snake_dir = to_west;

BOOL fruits_go = true;

// 果实坐标
int nx1 = 0;
int ny1 = 0;

// 蛇长
int snake_len = 3; 

// 分数
int snake_score = 0;