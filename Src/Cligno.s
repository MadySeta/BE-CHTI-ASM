	include ../Driver/DriverJeuLaser.inc
		
	EXPORT timer_callback ;remplace dans principal.c la fonction éponyme, définie en ASM ici
	EXPORT FlagCligno ;pour observation debug
	PRESERVE8
	THUMB 
		
; ====================== zone de réservation de données,  ======================================
;Section RAM (read only) :
	area    mesdata,data,readonly


;Section RAM (read write):
	area    maram,data,readwrite
; ===============================================================================================
	
FlagCligno dcd 1

		
;Section ROM code (read only) :		
	area    moncode,code,readonly

timer_callback proc
	push {r4,lr} ;on save lr dans la pile parce-qu'on réattribue lr (cf. bl)
	ldr r3,=FlagCligno
	ldr r4,[r3]
	cbz r4 , FlagNull ;si r4==0, on branch sur flagNull (on éteint la diode)
;sinon on l'allume
	mov r4 , #0
	str r4, [r3]
	mov r0, #1
	bl GPIOB_Set 
	b Sortie ;pour n'avoir qu'une seule sortie bx lr
FlagNull
	mov r4 , #1
	str r4, [r3]
	mov r0, #1
	bl GPIOB_Clear
Sortie
	pop {r4,lr}
	bx lr
	
	END