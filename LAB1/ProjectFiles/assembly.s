		AREA    |.text|, CODE, READONLY, ALIGN=2
 
f_asm	
        GLOBAL f_asm
		EXTERN graphicMemory
		EXTERN direction
		EXTERN velocity

        THUMB
		push{r0-r12}
		ldr r0, =graphicMemory
		ldr r1, =direction
		ldr r2, =velocity 
		ldrb r11, [r1]
		ldrb r6, [r2]

		; LOOP EXTERNO
		MOV   r1, #127 
EXTERNAL_LOOP

		; LOOP VELOCIDADE
		MOV   r2, r6
SPEED_LOOP
			mov r9, #0
			mov r4, #128
			mul r4, r1, r4

			cmp r11, #0
			beq MOVE_RIGHT
			
			cmp r11, #1
			beq MOVE_LEFT

			cmp r11, #2
			beq MOVE_UP

			cmp r11, #3
			beq MOVE_DOWN
				
MOVE_RIGHT
					add r9, r4, #127
					ldrb r5, [r0, r9] 	
					MOV   r3, #0
					mov r8, #0
MOVE_RIGHT_LOOP
					add r8, r4, r3
					ldrb r7, [r0, r8]
					EOR r7, r7, r5
					EOR r5, r5, r7
					EOR r7, r7, r5
					strb r7, [r0, r8]
					add r3, r3, #1
					cmp r3, #128
					bne MOVE_RIGHT_LOOP
					b CONTINUE

MOVE_LEFT
					ldrb r5, [r0, r4] 	
					MOV   r3, #127
					mov r8, #0
MOVE_LEFT_LOOP
					add r8, r4, r3
					ldrb r7, [r0, r8]
					EOR r7, r7, r5
					EOR r5, r5, r7
					EOR r7, r7, r5
					strb r7, [r0, r8]
					sub r3, r3, #1
					cmp r3, #-1
					bne MOVE_LEFT_LOOP
					b CONTINUE

MOVE_UP
					ldrb r5, [r0, r1]
					mov r8, #128					
					MOV r3, #127
MOVE_UP_LOOP
					mul r4, r3, r8
					add r4, r4, r1
					ldrb r7, [r0, r4]
					EOR r7, r7, r5
					EOR r5, r5, r7
					EOR r7, r7, r5
					strb r7, [r0, r4]
					sub r3, r3, #1
					cmp r3, #-1
					bne MOVE_UP_LOOP
					b CONTINUE

MOVE_DOWN
					add r9, r1, #(127*128)
					ldrb r5, [r0, r9]
					mov r8, #128						
					MOV   r3, #0
MOVE_DOWN_LOOP
					mul r4, r3, r8
					add r4, r4, r1
					ldrb r7, [r0, r4]
					EOR r7, r7, r5
					EOR r5, r5, r7
					EOR r7, r7, r5
					strb r7, [r0, r4]
					add r3, r3, #1
					cmp r3, #128
					bne MOVE_DOWN_LOOP
CONTINUE
   	 	SUBS  r2, r2, #1
		cmp r2, #0
  	    BNE	SPEED_LOOP
		; FIM SPEED LOOP

    	SUBS  r1, r1, #1
		cmp r1, #-1
        BNE EXTERNAL_LOOP
	; FIM LOOP EXTERNO
		POP{r0-r12}
        bx lr
		END