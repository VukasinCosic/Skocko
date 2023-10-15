void render_background()
{
	unsigned int* pixel = (unsigned int*)renderState.Memory;
	for (int y = 0; y < renderState.Height; y++)
	{
		for (int x = 0; x < renderState.Width; x++)
		{
			*pixel++ = 0x3399FF;
		}
	}
}

void clear_screen(unsigned int color) 
{
	unsigned int* pixel = (unsigned int*)renderState.Memory;
	for (int y = 0; y < renderState.Height; y++)
	{
		for (int x = 0; x < renderState.Width; x++)
		{
			*pixel++ = color;
		}
	}
}

void draw_rect_in_pixels(int x0, int y0, int x1, int y1, u32 color) 
{

	x0 = clamp(0, x0, renderState.Width);
	x1 = clamp(0, x1, renderState.Width);
	y0 = clamp(0, y0, renderState.Height);
	y1 = clamp(0, y1, renderState.Height);

	for (int y = y0; y < y1; y++) {
		u32* pixel = (u32*)renderState.Memory + x0 + y * renderState.Width;
		for (int x = x0; x < x1; x++) {
			*pixel++ = color;
		}
	}
}


void draw_rect(int x0, int y0, int x1, int y1, unsigned int color)
{
	x0 = clamp(0, x0, renderState.Width);
	x1 = clamp(0, x1, renderState.Width);
	y0 = clamp(0, y0, renderState.Height);
	y1 = clamp(0, y1, renderState.Height);


	for (int y = y0; y < y1; y++)
	{
		unsigned int* pixel = (unsigned int*)renderState.Memory + x0 + y * renderState.Width;
		for (int x = x0; x < x1; x++)
		{
			*pixel++ = color;
		}
	}
	
}

void draw_circle(int x, int y, int rad, unsigned int color)
{
	x = clamp(0, x, renderState.Width-rad);
	y = clamp(0, y, renderState.Height-rad);
	
	for (int i = y - rad; i < y + rad; i++)
	{
		unsigned int* pixel = (unsigned int*)renderState.Memory + x - rad + i * renderState.Width;
		for (int j = x - rad; j < x + rad; j++)
		{ 
			int sumsq = (x - j) * (x - j) + (y - i) * (y - i) - (rad-4) * (rad-4);
			if (sumsq <= 0)
			{
				*pixel++ = color;
			}
			else
			{
				*pixel++ = 0x000099;
			}
		}
	}
}

void set_board()
{
	int size_increase = 70;
	int x0_start = 100;
	int y0_start = 600;
	int x1_start = 150;
	int y1_start = 650;

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			draw_rect(x0_start, y0_start, x1_start, y1_start, 0x99ccff);
			x0_start += size_increase;
			x1_start += size_increase;
		}
		x0_start = 100;
		x1_start = 150;
		y0_start -= size_increase;
		y1_start -= size_increase;
	}

	int x_circle = 625;
	int y_circle = 625;

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			draw_circle(x_circle, y_circle, 25, 0x000000);
			x_circle += size_increase;
		}
		x_circle = 625;
		y_circle -= size_increase;
	}

	x0_start = 600;
	y0_start = 100;
	x1_start = 650;
	y1_start = 150;

	unsigned int colors[8] = {0x000000, 0xff0000, 0x00ff00, 0x0000ff, 0xffff00, 0xff00ff, 0x99ccff, 0x99ccff};

	for (int i = 0; i < 8; i++)
	{
		draw_rect(x0_start, y0_start, x1_start, y1_start, colors[i]);
		x0_start += size_increase;
		x1_start += size_increase;
	}
}