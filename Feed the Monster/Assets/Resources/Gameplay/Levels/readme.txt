Level XML variables
----------------------


XMLLevel
**************************
monsterInputType: type of pazle (Letter, LetterInWord, Word)
CollectableMonster: Monster type (Green, White, Blue, Pink)
LevelTemplete: backgrund type(LevelTempleteBlueSky, LevelTempleteNight, LevelTempletePinkSky, LevelTempleteYellowSky)

SegmentTime: time for each Segment in seconds
ShuffleSegment: boolean, "true" Shuffle Segment every time the level start
HideCallout: int, '-1' not hide, '0' hide, <'1' hide after ? blinks
LettersGroup: מספר מקבץ



Segment
**************************
spawnIds: put letters only  in locations from the list (split by comma)
SegmentTime: 


Stones( string )
**************************
content can be any letter or one of the boosters:
	FreezeTime: freeze segment timer for 5 seconds
	FireWrongLetter: blow an wrong letter
	LoseSegment: lose current segment 
	MagnetLetter: Magnet same letter or next letter to the draged letter
	SlowMovment: slow stone movement 
	ShowCallout: show callout for ? seconds
	BonusLetter: 
	Shield:		

spawnId
bonusScore
delayIn
delayRepet
speed
loop
hideAfter: seconds to hide
hideAfterBlinks: num of blinks before hide;
	
