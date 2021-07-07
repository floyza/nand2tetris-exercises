// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

	(MAIN_LOOP)
// Wait for key press
	(PRESS_LOOP)
	@KBD
	D=M
	@PRESS_LOOP
	D;JEQ

// Initialize screen drawing stuff
	@8192 // 256 rows, 32 words per row of 16 bits each
	D=A
	@WORD_COUNT
	M=D

	@SCREEN
	D=A
	@SCREEN_POS
	M=D

	(BLACK_LOOP)
// Dec and jump if done
	@WORD_COUNT
	M=M-1
	D=M
	@BLACK_END
	D;JLT

// Write all 1s to this word and go to next word
	D=-1
	@SCREEN_POS
	A=M
	M=D
	@SCREEN_POS
	M=M+1

	@BLACK_LOOP
	0;JMP
	(BLACK_END)

// Wait for key release
	(WAIT_LOOP)
	@KBD
	D=M
	@WAIT_LOOP
	D;JNE

// Initialize screen drawing stuff
	@8192 // 256 rows, 32 words per row of 16 bits each
	D=A
	@WORD_COUNT
	M=D

	@SCREEN
	D=A
	@SCREEN_POS
	M=D

	(WHITE_LOOP)
// Dec and jump if done
	@WORD_COUNT
	M=M-1
	D=M
	@WHITE_END
	D;JLT

// Write all 0s to this word and go to next word
	D=0
	@SCREEN_POS
	A=M
	M=D
	@SCREEN_POS
	M=M+1

	@WHITE_LOOP
	0;JMP
	(WHITE_END)

// Jump back to beginning
	@MAIN_LOOP
	0;JMP
