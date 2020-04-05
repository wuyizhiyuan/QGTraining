#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <ctype.h>
#include <stdbool.h>
#include "function.h"

int main(void)
{
	FixedWindow();
	while(1)
	{
		DrawBoundary();
		int times = 0;
		while(1)
		{
			calculate();
			if(++times > 8)
			{
				if(transit())
				{
					system("pause");
					break;
				}
				times -= 5;
			}
		}
	}
	return 0;
}
