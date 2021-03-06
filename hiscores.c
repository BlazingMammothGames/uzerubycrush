/*
	Ruby Crush for the Uzebox
	Copyright 2010, Kenton Hamaluik

	This file is part of Ruby Crush for the Uzebox.

	Ruby Crush for the Uzebox is free software: you can redistribute
	it and/or modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation, either version 3 of the
	License, or (at your option) any later version.

	Ruby Crush for the Uzebox is distributed in the hope that it
	will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with The Uzebox Implementation of Pentago.  If not, see
	<http://www.gnu.org/licenses/>.
*/

#define RUBYCRUSH_EEPROM_ID	(21)

struct EepromBlockStruct eeprom;

void SetHighScore(u8 number, u8 i1, u8 i2, u8 i3, u32 score)
{
	// calculate the offset byte we're starting at
	u8 offset = (number * 5);
	
	// set the initials
	eeprom.data[offset + 0] = (u8)((i1 << 3) | ((i2 & 28) >> 2));
	eeprom.data[offset + 1] = (u8)((i2 << 6) | ((i3 & 31) << 1));
	
	// set the score
	eeprom.data[offset + 2] = (u8)((score &0xff0000) >> 16);
	eeprom.data[offset + 3] = (u8)((score &0xff00) >>  8);
	eeprom.data[offset + 4] = (u8)((score &0xff));
}

void GetHighScore(u8 number, u8 *i1, u8 *i2, u8 *i3, u32 *score)
{
	// calculate the offset byte we're starting at
	u8 offset = (number * 5);
	
	// get the initials
	*i1 = eeprom.data[offset + 0] >> 3;
	*i2 = ((eeprom.data[offset + 0] & 7) << 2) | ((eeprom.data[offset + 1] & 192) >> 6);
	*i3 = (eeprom.data[offset + 1] & 62) >> 1;
	
	// get the score
	*score = (u32)(((u32)eeprom.data[offset + 2] << 16) | ((u32)eeprom.data[offset + 3] << 8) | ((u32)eeprom.data[offset + 4]));
}

void InitHighScores()
{
	// make sure we're formatted
	/*if(!isEepromFormatted())
		FormatEeprom();*/
		
	eeprom.id = RUBYCRUSH_EEPROM_ID;
		
	// now read in the struct
	EepromReadBlock(RUBYCRUSH_EEPROM_ID, &eeprom);
}

void WriteHighScores()
{
	// set the identifer bytes to be sure
	eeprom.id = RUBYCRUSH_EEPROM_ID;
	
	// write it out!
	EepromWriteBlock(&eeprom);
}

// check to see the rank of the current score
// if classic mode, timed = 0
// if timed mode, timed = 1
u8 GetScoreRank(u32 score, u8 timed)
{
	// we don't care about the initials here, so just use a dummy
	u8 i;
	
	// now the 3 highest classic mode scores..
	u32 score1, score2, score3;
	
	// now get the high scores
	GetHighScore(0 + (timed * 3), &i, &i, &i, &score1);
	GetHighScore(1 + (timed * 3), &i, &i, &i, &score2);
	GetHighScore(2 + (timed * 3), &i, &i, &i, &score3);
	
	if(score <= score3)
		// didn't make the cut!
		return 4;
	if(score <= score2)
		// beat score3, but not score2
		return 3;
	if(score <= score1)
		// beat score 2, but not score 1
		return 2;
	
	// the only way we get down here is if we beat score 1!
	return 1;
}

void NewHighScore(u8 i1, u8 i2, u8 i3, u32 score, u8 timed)
{
	u8 rank = GetScoreRank(score, timed);
	
	// shift the old scores down
	for(u8 i = rank; i < 3; i++)
	{
		u8 oi1, oi2, oi3;
		u32 oscore;
		GetHighScore(i - 1 + (timed * 3), &oi1, &oi2, &oi3, &oscore);
		SetHighScore(i + (timed * 3), oi1, oi2, oi3, oscore);
	}
	
	// set the new score
	SetHighScore(rank - 1 + (timed * 3), i1, i2, i3, score);
	
	// and write it out
	WriteHighScores();
}