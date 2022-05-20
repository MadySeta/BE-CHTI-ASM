	PRESERVE8
	THUMB   
	include ../../Driver/DriverJeuLaser.inc


; ====================== zone de réservation de données,  ======================================
;Section RAM (read only) :
	area    mesdata,data,readonly


;Section RAM (read write):
	area    maram,data,readwrite
		
			
; ===============================================================================================


index dcd 0
SortieSon dcw 0
		
;Section ROM code (read only) :		
	area    moncode,code,readonly
; écrire le code ici		


	EXPORT index
	EXPORT SortieSon
	EXPORT CallbackSon
	EXPORT StartSon

	IMPORT Son
	IMPORT LongueurSon
	
	
CallbackSon proc
		push {r4,r5,r6,lr}
reprise	ldr r0, =index
		ldr r3, [r0]
		
		ldr r1, =SortieSon
		
		ldr r2, =Son
		

		ldr r4, =LongueurSon
		ldr r5, [r4]
		
		cmp r3, r5
		bgt stop
		
		ldrsh r6, [r2, r3, lsl#1]
		;lsr r6, r6, #16
		add r6,#32768
		mov r2, #720
		mul r6, r2
		asr r6, #16
		strh r6,[r1]
		

		mov r0, r6

		bl PWM_Set_Value_TIM3_Ch3
	
		add r3, #1
		ldr r0, =index
		str r3, [r0]
		b stop
		
stop	pop {r4, r5, r6,lr}
		bx lr
		endp	
		
StartSon proc
		ldr r1, =index
		mov r2, #0
		str r2, [r1]
		bx lr
		endp
	END
		