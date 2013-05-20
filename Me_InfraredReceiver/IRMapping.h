#ifndef IRMAPPING_H
#define IRMAPPING_H

// Mapped commands - (Decode routine maps raw values to these)
enum IRButtons {POWER_BUTTON = 100, UNKOWN_BUTTON = 101, MENU_BUTTON = 102,
				   TEST_BUTTON = 103 , PLUS_BUTTON = 104, RETURN_BUTTON = 105,
				   PREVIOUS_BUTTON = 106, PLAY_BUTTON = 107, NEXT_BUTTON = 108, 
				   MINUS_BUTTON = 109, CLR_BUTTON = 110,};
                               

// Raw Values from remote
// Change these to match the raw values from your remote.
#define RAW_POWER_BUTTON 23842
#define RAW_UNKOWN_BUTTON 23715
#define RAW_MENU_BUTTON 23587
#define RAW_TEST_BUTTON 23970
#define RAW_PLUS_BUTTON 24480
#define RAW_RETURN_BUTTON 24097
#define RAW_PREVIOUS_BUTTON 31747
#define RAW_PLAY_BUTTON 29962
#define RAW_NEXT_BUTTON 31492
#define RAW_MINUS_BUTTON 29452
#define RAW_CLR_BUTTON 30982
#define RAW_0 29835
#define RAW_1 31110
#define RAW_2 29580
#define RAW_3 20655
#define RAW_4 31620
#define RAW_5 29070
#define RAW_6 21165
#define RAW_7 24225
#define RAW_8 22185
#define RAW_9 23205

#endif // IRMAPPING_H
