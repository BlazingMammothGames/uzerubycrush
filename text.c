/*
	Bejeweled for the Uzebox
	Copyright 2010, Kenton Hamaluik

	This file is part of The Uzebox Implementation of Pentago.

	The Uzebox Implementation of Pentago is free software: you can redistribute
	it and/or modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation, either version 3 of the
	License, or (at your option) any later version.

	The Uzebox Implementation of Pentago is distributed in the hope that it
	will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with The Uzebox Implementation of Pentago.  If not, see
	<http://www.gnu.org/licenses/>.
*/

// drawing functions

void InitText()
{
	// set the screen tiles
	SetTileTable(tiles_atascii);
	
	// fill the bg
	Fill(0, 0, 30, 28, ' ');
}

void PrintStr(char x, char y, char *string)
{
	char cx = x;
	for(char i = 0; i < strlen(string); i++)
	{
		if(string[i] == '\n')
		{
			cx = x;
			y++;
		}
		else
		{
			SetTile(cx, y, string[i]);
			cx++;
		}
	}
}

void PrintStr_P(char x, char y, char *string)
{
	char cx = x;
	char c;
	int i = 0;
	
	while(1)
	{
		c = pgm_read_byte(&(string[i++]));
		
		if(c == '\0')
		{
			break;
		}
		else if(c == '\n')
		{
			cx = x;
			y++;
		}
		else
		{
			SetTile(cx, y, c);
			cx++;
		}
	}
}

void PrintStrCenter(char y, char *string)
{
	char x = (30 - strlen(string)) / 2;
	PrintStr(x, y, string);
}

void PrintStrCenter_P(char y, char *string)
{
	char x = (30 - strlen_P(string)) / 2;
	PrintStr_P(x, y, string);
}
