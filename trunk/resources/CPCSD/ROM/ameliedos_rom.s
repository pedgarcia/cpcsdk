; ---------------------------------------------------------------------------
; AMÉLIE ROM (c) 2012
; ---------------------------------------------------------------------------

; Assembly with:
; vasmz80_oldstyle ameliedos_rom.s -o ameliedos.rom -L ameliedos_rom.lst -Fbin -z80asm

;  9   AMSDOS, XDPB
; 10.7 Examples of searching ROM commands
; 19   AMSDOS BIOS Facilities
; 20   AMSDOS External Commands

; Amélie need to be in a lower rom position than Amsdos.

; TODO: 
; .- Extract the drive number from the strings passed as parameters at the 
;    RSXs (REN, ERA, DIR).
; .- Extend the parameters of rsx_read_sector, rsx_write_sector and 
;    rsx_format_track when the drive is the SD. Or use directly the SD CMDs
;    variables.
; .- Adding support for machines without disk rom.

; Constants
SD_DRIVE_NUMBER             EQU 2   ; A = 0 | B = 1 | C = SD = 2

    include 'firmware.i'

    ORG  $C000

; ---------------------------------------------------------------------------
; ROM Header
rom_type
    DEFB 1                          ; Background ROM

rom_version
    DEFB 0,0,1

; ---------------------------------------------------------------------------
rsx_names
    DEFW rsx_name_table

; ---------------------------------------------------------------------------
    JP   initialize_amelie          ; RSX AMÉLIE DOS

; ---------------------------------------------------------------------------
amelie_extra_rsxs
    JP   rsx_sd                     ; |SD
    JP   rsx_sd                     ; |C
;    JP   rsx_change_dir             ; |CD
;    JP   rsx_make_dir               ; |MD
;    JP   rsx_delete_dir             ; |RD
;    JP   rsx_format_sd              ; |FORMAT
;    JP   ...                        ; |

; ---------------------------------------------------------------------------
amsdos_overloaded_rsxs
    JP   rsx_drive                  ; |DRIVE
    JP   rsx_dir                    ; |DIR
    JP   rsx_era                    ; |ERA
    JP   rsx_ren                    ; |REN

    ; Hidden RSXs
    JP   rsx_read_sector            ; Read Sector (|^D)
    JP   rsx_write_sector           ; Write Sector (|^E)
    JP   rsx_format_track           ; Format Track (|^F)

; ---------------------------------------------------------------------------
amelie_cas_vectors
    JP   amelie_cas_in_open         ; CAS_IN_OPEN (LOAD 3, OPENIN 1, MERGE 3, RUN 3)
    JP   amelie_cas_in_close        ; CAS_IN_CLOSE (LOAD 5, CLOSEIN 1, MERGE 5, RUN 5)
    JP   amelie_cas_in_abandon      ; CAS_IN_ABANDON (CAT 1, LOAD 1, SAVE 1, MERGE 1, RUN 1)
    JP   amelie_cas_in_char         ; CAS_IN_CHAR (MERGE 4)
    JP   amelie_cas_in_direct       ; CAS_IN_DIRECT (LOAD 4, RUN 4)
    JP   amelie_cas_return          ; CAS_RETURN
    JP   amelie_cas_test_eof        ; CAS_TEST_EOF
    JP   amelie_cas_out_open        ; CAS_OUT_OPEN (SAVE 3 y OPENOUT 1)
    JP   amelie_cas_out_close       ; CAS_OUT_CLOSE (SAVE 5, CLOSEOUT 1, CHAIN MERGE 6, RUN 6)
    JP   amelie_cas_out_abandon     ; CAS_OUT_ABANDON (CAT 2, LOAD 2, SAVE 2, MERGE 2, RUN 2)
    JP   amelie_cas_out_char        ; CAS_OUT_CHAR
    JP   amelie_cas_out_direct      ; CAS_OUT_DIRECT (SAVE 4)
    JP   amelie_cas_catalog         ; CAS_CATALOG (CAT 3)

; ---------------------------------------------------------------------------
rsx_name_table
    DEFB 'AMELIE DO','S' + $80

    ; Amélie extra RSXs
    DEFB 'S', 'D' + $80
    DEFB 'C' + $80
;    DEFB 'C', 'D' + $80
;    DEFB 'M', 'D' + $80
;    DEFB 'RMDI', 'R' + $80
;    DEFB 'FORMA', 'T' + $80
;    DEFB '', '' + $80

    ; Amsdos overloaded RSXs
    DEFB 'DRIV', 'E' + $80
    DEFB 'DI', 'R' + $80
    DEFB 'ER', 'A' + $80
    DEFB 'RE', 'N' + $80

    ; Amsdos Hidden RSXs
;    DEFB $81                        ; Set Message (Not need to overload)
;    DEFB $82                        ; Set Drive Speed (Not need to overload)
;    DEFB $83                        ; Set Disk Type (Not need to overload)
    DEFB $84                        ; Read Sector
    DEFB $85                        ; Write Sector
    DEFB $86                        ; Format Track
;    DEFB $87                        ; Seek Track (Not need to overload)
;    DEFB $88                        ; Test Drive (Not need to overload)
;    DEFB $89                        ; Set Retry Count (Not need to overload)

    DEFB 0                          ; End RSX name table

; ---------------------------------------------------------------------------
; Jump to Amélie CAS vectors
; ---------------------------------------------------------------------------
amelie_cas_hook
    PUSH HL
    PUSH DE
    PUSH AF
    LD   IY,(AMSDOS_MEMORY_POOL)
    LD   HL,14
    ADD  HL,SP
    LD   E,(HL)
    INC  HL
    LD   D,(HL)
    LD   HL,(amsdos_cas_vectors)
    EX   DE,HL
    AND  A
    SBC  HL,DE                      ; AMSDOS_CAS_VECTOR - AMSDOS_VECTOR_CALLED
    LD   A,H
    OR   A
    JR   NZ,.no_amsdos_cas_vector
    LD   A,L
    CP   13 * 3 
    JR   NC,.no_amsdos_cas_vector

    ; Update the jump to the Amélie CAS vectors
    LD   DE,amelie_cas_vectors
    ADD  HL,DE
    POP  AF
    POP  DE
    EX   (SP),HL
    RET

.no_amsdos_cas_vector
    POP  AF
    POP  DE
    POP  HL
    RET

; ---------------------------------------------------------------------------
; Check for the active drive and prepare return address for firmware
; ---------------------------------------------------------------------------
check_drive_and_prepare_return_for_cas
    PUSH AF
    LD   A,(IY + AMSDOS_FCB_OPENIN + FCB_DRIVE_NUMBER)
    CP   SD_DRIVE_NUMBER                    ; Is SD?
    JR   NZ,.make_amsdos_cas_vector_call    ; No, then call AMSDOS CAS vector
    
    ; Yes, then we need to update the return address for after our patched CAS vector
.update_stack_for_return_from_cas_vector
    PUSH HL
    LD   HL,14
    ADD  HL,SP          ; HL = SP + 14
    LD   (HL),$0F
    INC  HL
    LD   (HL),0         ; Change to $000F -> RET in Lower ROM
    POP  HL

.make_amsdos_cas_vector_call
    POP  AF
    RET

; ---------------------------------------------------------------------------
; Amélie CAS vectors
; ---------------------------------------------------------------------------
; CAS_IN_OPEN: Open a file for input.
; ENTRIES:
;     B : Length filename.
;    HL : Address filename.
;    DE : Address of 2 KBs buffer.
; EXITS:
;   * If file was opened OK:
;     Carry true and Zero false.
;     HL : Adress of buffer with the file header.
;     DE : File load Address.
;     BC : File length.
;      A : File type.
;   * If the stream was in use:
;     Carry and Zero false.
;      A : Error code.
;     BC, DE, HL corrupt.
;   * If the user pressed ESC:
;     Carry false and Zero true.
;      A : Error code.
;     BC, DE, HL corrupt.
;   * Always:
;     IX and the other flags corrupt. 
;     All others registers preserved.
; ---------------------------------------------------------------------------
amelie_cas_in_open
    ; Check for the active drive and prepare return address for firmware
    CALL check_drive_and_prepare_return_for_cas

    ; Make Amélie code

    ; Return to firmware
    SCF                                             ; Carry True
    SBC  A,A                                        ; Zero False
;    LD   A,(IY + AMSDOS_FH_OPENIN + FH_FILE_TYPE)   ; A -> File type from the header
    RET

; ---------------------------------------------------------------------------
; CAS_IN_CLOSE: Close the input file properly.
; EXITS:
;   * If the stream was closed OK:
;     Carry true.
;      A corrupt.
;   * If the stream was not open:
;     Carry false.
;      A : Error code.
;   * Always:
;     BC, DE, HL and other flags corrupt.
;     All others registers preserved.
; ---------------------------------------------------------------------------
amelie_cas_in_close
    ; Check for the active drive and prepare return address for firmware
    CALL check_drive_and_prepare_return_for_cas

    ; Make Amélie code

    ; Return to firmware
    SCF                             ; Carry True
    RET

; ---------------------------------------------------------------------------
; CAS_IN_ABANDON: Close the input file immediately.
; EXITS:
;     AF, BC, DE and HL corrupt.
;     All others registers preserved.
; ---------------------------------------------------------------------------
amelie_cas_in_abandon
    ; Check for the active drive and prepare return address for firmware
    CALL check_drive_and_prepare_return_for_cas

    ; Make Amélie code

    ; Return to firmware
    RET

; ---------------------------------------------------------------------------
; CAS_IN_CHAR: read a character from the input file.
; EXITS:
;   * If the character was read OK:
;     Carry true and Zero false.
;      A : Character read from the file.
;   * If the end of the file was found:
;     Carry and Zero false.
;      A : Error code.
;   * If the user pressed ESC:
;     Carry false and Zero true.
;      A : Error code.
;   * Always:
;     IX and the other flags corrupt. 
;     All others registers preserved.
; ---------------------------------------------------------------------------
amelie_cas_in_char
    ; Check for the active drive and prepare return address for firmware
    CALL check_drive_and_prepare_return_for_cas

    ; Make Amélie code

    ; Return to firmware
    SCF                             ; Carry True
    RET

; ---------------------------------------------------------------------------
; CAS_IN_DIRECT: Read the input file into store.
; ENTRIES:
;     HL: Address where put the file.
; EXITS:
;   * If the file was read OK:
;     Carry true and Zero false.
;     HL : Character read from the file.
;      A corrupt. 
;   * If the file was not open as expected:
;     Carry and Zero false.
;      A : Error code.
;     HL corrupt.
;   * If the user pressed ESC:
;     Carry false and Zero true.
;      A : Error code.
;     HL corrupt.
;   * Always:
;     BC, DE, HL, IX and the other flags corrupt. 
;     All others registers preserved.
; ---------------------------------------------------------------------------
amelie_cas_in_direct
    ; Check for the active drive and prepare return address for firmware
    CALL check_drive_and_prepare_return_for_cas

    ; Make Amélie code

    ; Return to firmware
    SCF                             ; Carry True
    RET

; ---------------------------------------------------------------------------
; CAS_RETURN: Put the last character read back.
; EXITS:
;     All registers and flags preserved.
; ---------------------------------------------------------------------------
amelie_cas_return
    ; Check for the active drive and prepare return address for firmware
    CALL check_drive_and_prepare_return_for_cas

    ; Make Amélie code

    ; Return to firmware
    RET

; ---------------------------------------------------------------------------
; CAS_TEST_EOF: Have we reached the end of the input file yet?
; EXITS:
;   * If the end of the file was not found:
;     Carry true and Zero false.
;     A corrupt.
;   * If the end of the file was found:
;     Carry and Zero false.
;     A corrupt.
;   * If the user pressed ESC:
;     Carry false and Zero true.
;      A : Error code.
;   * Always:
;     IX and the other flags corrupt.
;     All others registers preserved.
; ---------------------------------------------------------------------------
amelie_cas_test_eof
    ; Check for the active drive and prepare return address for firmware
    CALL check_drive_and_prepare_return_for_cas

    ; Make Amélie code

    ; Return to firmware
    SCF                             ; Carry True
    RET

; ---------------------------------------------------------------------------
; CAS_OUT_OPEN: Open a file for output.
; ENTRIES:
;     B : Length filename.
;    HL : Address filename.
;    DE : Address of 2 KBs buffer.
; EXITS:
;   * If file was opened OK:
;     Carry true and Zero false.
;     HL : Adress of buffer with the file header.
;     A corrupt.
;   * If the stream was in use:
;     Carry and Zero false.
;      A : Error code
;     HL corrupt
;   * If the user pressed ESC:
;     Carry false and Zero true.
;      A : Error code
;     HL corrupt
;   * Always:
;     BC, DE, IX and the other flags corrupt. 
;     All others registers preserved.
; ---------------------------------------------------------------------------
amelie_cas_out_open
    ; Check for the active drive and prepare return address for firmware
    CALL check_drive_and_prepare_return_for_cas

    ; Make Amélie code

    ; Return to firmware
    SCF                             ; Carry True
    RET

; ---------------------------------------------------------------------------
; CAS_OUT_CLOSE: Close the output file properly.
; EXITS:
;   * If the stream was closed OK:
;     Carry true and Zero false.
;      A corrupt.
;   * If the stream was not open:
;     Carry and Zero false.
;      A : Error code.
;   * If the user pressed ESC:
;     Carry false and Zero true.
;      A : Error code.
;   * Always:
;     BC, DE, HL, IX and other flags corrupt.
;     All others registers preserved.
; ---------------------------------------------------------------------------
amelie_cas_out_close
    ; Check for the active drive and prepare return address for firmware
    CALL check_drive_and_prepare_return_for_cas

    ; Make Amélie code

    ; Return to firmware
    SCF                             ; Carry True
    RET

; ---------------------------------------------------------------------------
; CAS_OUT_ABANDON: Close the output file immediately.
; EXITS:
;     AF, BC, DE and HL corrupt.
;     All others registers preserved.
; ---------------------------------------------------------------------------
amelie_cas_out_abandon
    ; Check for the active drive and prepare return address for firmware
    CALL check_drive_and_prepare_return_for_cas

    ; Make Amélie code

    ; Return to firmware
    RET

; ---------------------------------------------------------------------------
; CAS_OUT_CHAR: Write a character to the output file.
; ENTRIES:
;      A : Character to write.
; EXITS:
;   * If the character was written OK:
;     Carry true and Zero false.
;      A corrupt.
;   * If the file was not open as expected:
;     Carry and Zero false.
;      A : Error code.
;   * If the user pressed ESC:
;     Carry false and Zero true.
;      A : Error code.
;   * Always:
;     IX and the other flags corrupt. 
;     All others registers preserved.
; ---------------------------------------------------------------------------
amelie_cas_out_char
    ; Check for the active drive and prepare return address for firmware
    CALL check_drive_and_prepare_return_for_cas

    ; Make Amélie code

    ; Return to firmware
    SCF                             ; Carry True
    RET

; ---------------------------------------------------------------------------
; CAS_OUT_DIRECT: Write the output file directly from store.
; ENTRIES:
;     HL : Addres of the data to write.
;     DE : Length of the data to write.
;     BC : Execute address for the header.
;      A : File type for the header.
; EXITS:
;   * If the file was written OK:
;     Carry true and Zero false.
;      A corrupt.
;   * If the file was not open:
;     Carry and Zero false.
;      A : Error code.
;   * If the user pressed ESC:
;     Carry false and Zero true.
;      A : Error code.
;   * Always:
;     BC, DE, HL, IX and the other flags corrupt. 
;     All others registers preserved.
; ---------------------------------------------------------------------------
amelie_cas_out_direct
    ; Check for the active drive and prepare return address for firmware
    CALL check_drive_and_prepare_return_for_cas

    ; Make Amélie code

    ; Return to firmware
    SCF                             ; Carry True
    RET

; ---------------------------------------------------------------------------
; CAS_CATALOG: Generate a catalogue from the tape.
; ENTRIES:
;     DE : Address of 2 KBs buffer.
; EXITS:
;   * If the cataloguing went OK:
;     Carry true and Zero false.
;      A corrupt.
;   * If the read stream was in use:
;     Carry and Zero false.
;      A : Error code.
;   * If an error ocurred:
;     Carry false and Zero true.
;      A : Error code.
;   * Always:
;     BC, DE, HL, IX and the other flags corrupt. 
;     All others registers preserved.
; ---------------------------------------------------------------------------
amelie_cas_catalog
    ; Check for the active drive and prepare return address for firmware
    CALL check_drive_and_prepare_return_for_cas

    ; Make Amélie code

    ; Return to firmware
    SCF                             ; Carry True
    RET

; ---------------------------------------------------------------------------
; Amélie RSXs
; ---------------------------------------------------------------------------
; |DIR
; ---------------------------------------------------------------------------
rsx_dir
    CALL save_return_address_for_errors
    PUSH AF
    PUSH IX

    LD   C,A                        ; Save number of parameters (BC can be used freely)
    ; Check for the active drive
    CALL is_sd_active_drive
    JR   NZ,.make_amsdos_call

    ; |DIR Amélie code
    LD   A,C
    OR   A
    CALL NZ,get_string_param        ; HL = String

    ; Return to firmware
    OR   A                          ; Carry False
    RET

    ; It's not the SD drive, we redirect to the AMSDOS |DIR RSX
.make_amsdos_call
    POP  IX
    POP  AF
    RST  $18                        ; FAR_CALL AMSDOS |DIR
    DEFW farcall_amsdos_dir

    RET

; ---------------------------------------------------------------------------
; |ERA
; ---------------------------------------------------------------------------
rsx_era
    CALL save_return_address_for_errors
    PUSH AF
    PUSH IX

    CALL test_for_single_param

;    CALL get_string_param           ; HL = String

    ; Check for the drive in the parameter
;;    CALL is_sd_active_drive
;    LD   A,(BC)
;    CP   SD_DRIVE_NUMBER
;    JR   NZ,.make_amsdos_call

    ; |ERA Amélie code
;    CALL enable_parameter_drive


;   JP   return_from_rsx            ; RET
    ; Return to firmware
    OR   A                          ; Carry False
    RET

    ; It's not the SD drive, we redirect to the AMSDOS |ERA RSX
.make_amsdos_call
    POP  IX
    POP  AF
    RST  $18                        ; FAR_CALL AMSDOS |ERA
    DEFW farcall_amsdos_era

    RET

; ---------------------------------------------------------------------------
enable_parameter_drive
    LD   A,(BC)                     ; Get drive number from parameter
    INC  BC

    PUSH AF
    CALL set_active_drive
    POP  AF
    RET

; ---------------------------------------------------------------------------
; |REN
; Amsdos send an error in case of rename a file using differents drives.
; ---------------------------------------------------------------------------
rsx_ren
    CALL save_return_address_for_errors
    PUSH AF
    PUSH IX

    ; Test for the 2 parameters
    DEC  A                          ; DEC Number of Parameters
    CALL test_for_single_param

    ; Check for the active drive
    CALL is_sd_active_drive
    JR   NZ,.make_amsdos_call

    ; |REN Amélie code
;    CALL get_string_param           ; HL = String
    
    ; Get second parameter
;    CALL get_string_param           ; HL = String

    ; Return to firmware
    OR   A                          ; Carry False
    RET

    ; It's not the SD drive, we redirect to the AMSDOS |REN RSX
.make_amsdos_call
    POP  IX
    POP  AF
    RST  $18                        ; FAR_CALL AMSDOS |REN
    DEFW farcall_amsdos_ren

    RET

; ---------------------------------------------------------------------------
; |DRIVE
; ---------------------------------------------------------------------------
rsx_drive
    CALL save_return_address_for_errors
    
    PUSH AF
    PUSH IX
    CALL test_for_single_param

    CALL get_string_param           ; HL = String

    ; Get Drive Number
    RST  $20                        ; RAM LAM -> LD A,(HL)
    RES  5,A                        ; Uppercase
    CP   'S'                        ; is SD?
    JR   Z,.call_rsx_sd             ; Yes, then execute Amélie code
    CP   'C'                        ; is SD?
    JR   Z,.call_rsx_sd             ; Yes, then execute Amélie code

    ; It's not the SD drive, we redirect to the AMSDOS |DRIVE RSX
.make_amsdos_call
    POP  IX
    POP  AF
    RST  $18                        ; FAR_CALL AMSDOS |DRIVE
    DEFW farcall_amsdos_drive

    RET

.call_rsx_sd
    POP  IX
    POP  AF

; ---------------------------------------------------------------------------
; |SD
; ENTRIES:
;    IY: Amsdos Memory Pool (default $A700)
; ---------------------------------------------------------------------------
rsx_sd
    LD   A,SD_DRIVE_NUMBER

set_active_drive
    PUSH DE
    LD   E,$FF                                          ; Drive CLOSE flag
    CP   (IY + AMSDOS_FCB_OPENIN + FCB_DRIVE_NUMBER)    ; Extended File Control Block for OPENIN
    JR   Z,.drive_in_use                                ; Drive in use?
    CP   (IY + AMSDOS_FCB_OPENOUT + FCB_DRIVE_NUMBER)   ; Extended File Control Block for OPENOUT
    JR   Z,.drive_in_use                                ; Drive in use?
    INC  E                                              ; Drive OPEN

.drive_in_use
    LD   (AMSDOS_DRIVE_HSUS),A                          ; Drive HS/US
    LD   (IY + AMSDOS_DEFAULT_DRIVE),A                  ; Set Amsdos default drive
    LD   (IY + AMSDOS_ACTIVE_DRIVE),A                   ; Amsdos Active Drive

    ; We can ignore this and leave the amsdos XDPB, because we are not using it.
;    LD   (IY + AMSDOS_DPH_ACTIVE_DRIVE),$xx            ; Pointer to the XDPB for the Active Drive
;    LD   (IY + AMSDOS_DPH_ACTIVE_DRIVE + 1),$xx        ; (default $A910 or $A920)

    LD   (IY + AMSDOS_DEFAULT_DRIVE_OPEN),E             ; Set Flag if OPEN on Default Drive
    POP  DE

    RET

; File control block
; Drive Number + User + Filename (11 caracteres) +
; + Read Only + System + ...

; ---------------------------------------------------------------------------
; Read Sector (^D ó $84)
; ENTRIES:
;    HL : Address of sector buffer.
;     E : Drive number.
;     D : Track number.
;     C : Sector number.
; EXITS:
;   * If the sector was read OK:
;     Carry true.
;      A : 0
;     HL : Preserved.
;   * If an error ocurred:
;     Carry false.
;      A : Error status.
;     HL : Error status buffer.
;   * Always:
;     Other flags corrupt. 
;     All others registers preserved.
;
; NOTE: The sector buffer can lie even under ROM.
; ---------------------------------------------------------------------------
rsx_read_sector
    LD   A,SD_DRIVE_NUMBER
    CP   E
    JR   NZ,.make_amsdos_call
    ; |^D Amélie code

    ; Return to firmware
    SCF                             ; Carry True
    RET

    ; It's not the SD drive, we redirect to the AMSDOS |^D RSX
.make_amsdos_call
    RST  $18                        ; FAR_CALL AMSDOS |^D
    DEFW farcall_amsdos_read_sector
    RET

; ---------------------------------------------------------------------------
; Write Sector (^E ó $85)
; ENTRIES:
;    HL : Address of sector buffer.
;     E : Drive number.
;     D : Track number.
;     C : Sector number.
; EXITS:
;   * If the sector was written OK:
;     Carry true.
;      A : 0.
;     HL : Preserved.
;   * If an error ocurred:
;     Carry false.
;      A : Error status.
;     HL : Error status buffer.
;   * Always:
;     Other flags corrupt. 
;     All others registers preserved.
;
; NOTE: The sector buffer can lie even under ROM.
; ---------------------------------------------------------------------------
rsx_write_sector
    LD   A,SD_DRIVE_NUMBER
    CP   E
    JR   NZ,.make_amsdos_call
    ; |^E Amélie code

    ; Return to firmware
    SCF                             ; Carry True
    RET

    ; It's not the SD drive, we redirect to the AMSDOS |^E RSX
.make_amsdos_call
    RST  $18                        ; FAR_CALL AMSDOS |^E
    DEFW farcall_amsdos_write_sector
    RET

; ---------------------------------------------------------------------------
; Format Track (^F ó $86)
; ENTRIES:
;    HL : Address of header information buffer.
;     E : Drive number.
;     D : Track number.
; EXITS:
;   * If the track was formatted OK:
;     Carry true.
;      A : 0.
;     HL : Preserved.
;   * If an error ocurred:
;     Carry false.
;      A : Error status.
;     HL : Error status buffer.
;   * Always:
;     Other flags corrupt. 
;     All others registers preserved.
; ---------------------------------------------------------------------------
rsx_format_track
    LD   A,SD_DRIVE_NUMBER
    CP   E
    JR   NZ,.make_amsdos_call
    ; |^F Amélie code

    ; Return to firmware
    SCF                             ; Carry True
    RET

    ; It's not the SD drive, we redirect to the AMSDOS |^F RSX
.make_amsdos_call
    RST  $18                        ; FAR_CALL AMSDOS |^F
    DEFW farcall_amsdos_format_track
    RET

; ---------------------------------------------------------------------------
; Save return address in case of error
; ---------------------------------------------------------------------------
save_return_address_for_errors
    PUSH HL
    LD   HL,6
    ADD  HL,SP
    LD   (IY + AMSDOS_STACK_POINTER),L      ; Update AMSDOS stack pointer
    LD   (IY + AMSDOS_STACK_POINTER + 1),H
    POP  HL
    RET

; ---------------------------------------------------------------------------
; Carry False
; ---------------------------------------------------------------------------
;return_from_rsx
;    LD   L,(IY + AMSDOS_STACK_POINTER)      ; Update AMSDOS stack pointer
;    LD   H,(IY + AMSDOS_STACK_POINTER + 1)
;    LD   SP,HL                  ; Restore stack pointer
;    RET

; ---------------------------------------------------------------------------
; Test for a single parameter
; ENTRIES:
;     A: Number of parameters
; ---------------------------------------------------------------------------
test_for_single_param
    DEC  A
    RET  Z

    ; ERROR "Too many parameters"
;;;    LD   A,error_number
;    LD   HL,error_message
;;;;    CALL show_error

    ; Convert error code for the system
;;;    ADD  A,$0C
;;;    OR   $80
;;;    CP   A

    ; And return from the bug "gracefully"
    LD   L,(IY + AMSDOS_STACK_POINTER)
    LD   H,(IY + AMSDOS_STACK_POINTER + 1)  ; Recover AMSDOS stack pointer
    LD   SP,HL                              ; Set SP to it
    RET

; ---------------------------------------------------------------------------
; Get a pointer to an string parameter
; EXITS:
;     HL : String Address
;      B : String length
; ---------------------------------------------------------------------------
get_string_param
    CALL get_string_descriptor
    LD   B,(HL)                     ; String length
    INC  HL
    JP   load_hl_from_hl

get_string_descriptor    
    LD   L,(IX + 0)
    LD   H,(IX + 1)
    INC  IX
    INC  IX
    RET

; ---------------------------------------------------------------------------
; LD HL,(HL)
; ---------------------------------------------------------------------------
load_hl_from_hl
    PUSH AF
    LD   A,(HL)
    INC  HL
    LD   H,(HL)
    LD   L,A
    POP  AF
    RET

; ---------------------------------------------------------------------------
; Check if the SD is the active drive.
; EXITS:
;    Zero flag true if SD is the active drive.
;     A and HL corrupt. 
; ---------------------------------------------------------------------------
is_sd_active_drive
    LD   HL,(AMSDOS_MEMORY_POOL)
    INC  HL
    INC  HL
    LD   A,(HL)                     ; AMSDOS_MEMORY_POOL + 2 = Active Drive Number
    CP   SD_DRIVE_NUMBER
    RET

; ---------------------------------------------------------------------------
; Initialization
; ENTRIES:
;     DE: Pointer to the lowest RAM address that we can use.
;     HL: Pointer to the highest RAM address that we can use.
; EXITS:
;     Carry true.
;     DE: Pointer to the new lowest RAM address that we can use.
;     HL: Pointer to the new highest RAM address that we can use.
;     A, BC and the other flags corrupt. 
;     All others registers preserved.
; ---------------------------------------------------------------------------
initialize_amelie
    PUSH  HL
    PUSH  DE

;;;    CALL test_checksum_rom       ; Suma de todos los bytes de la rom, excepto el último que es el checksum
;;;    JR   NC,.checksum_failed

    LD    HL,initialize_text
    CALL  print_text

;;;    CALL test_hardware            ; Test & Initialize SD
;;;    JR   NC,.hardware_test_failed

    CALL init_workspace
    JR   NC,.init_workspace_failed

.exit_initialize_amelie
    POP   DE
    POP   HL
    SCF
    RET

;.checksum_failed
;    LD   HL,checksum_failed_text
;    JR   .print_error

;.hardware_test_failed
;    LD   HL,hardware_test_failed_text
;    JR   .print_error

.init_workspace_failed
    LD   HL,init_workspace_failed_text

.print_error
    CALL print_text
    JR   .exit_initialize_amelie

;checksum_failed_text
;    DEFB 'Ameli rom checksum failed.',10,13,$FF

;hardware_test_failed_text
;    DEFB 'SD Card was not found.',10,13,$FF

init_workspace_failed_text
    DEFB ' Amsdos or compatible was not found.',10,13,$FF

; ---------------------------------------------------------------------------
; 
; EXITS:
;     Carry false in case of error.
; ---------------------------------------------------------------------------
init_workspace
;    ; Check if the workspace is already initialized. *** AMSDOS always corrupt $BE7F ***
;    LD   DE,begin_ameliedos_patch
;    LD   HL,AMSDOS_HOOK
;    LD   B,3
;.loop_check_workspace
;    LD   A,(DE)
;    CP   (HL)
;    JR   NZ,.continue_with_initialization
;    INC  DE
;    INC  HL
;    DJNZ .loop_check_workspace

;    JR   .exit_init_workspace
;.continue_with_initialization

    ; Test for Amsdos or another compatible disk rom
    LD   HL,AMSDOS_HOOK + 1         ; First byte free after Amsdos workzone ($BE40 - $BE7F)
    LD   (HL),$C1                   ; BIOS SET MESSAGE (Amsdos)
    CALL KL_FIND_COMMAND
    RET  NC                         ; Exit if Amsdos is not detected

    ; Copy patch to ram, needed for the next routines
    LD   HL,begin_ameliedos_patch
    LD   DE,AMSDOS_HOOK
    LD   BC,end_ameliedos_patch - begin_ameliedos_patch
    LDIR

    ; Get the ROM number for the CAS vector hook
    CALL KL_CURR_SELECTION          ; A = ROM select address for our rom
    LD   (amelie_cas_hook_far_call + 2),A

    ; Get AMSDOS offset to the CAS vectors in the ROM
    CALL get_amsdos_cas_vectors
    LD   (amsdos_cas_vectors),HL    ; (CPC = $CD4C / CPC+ = $CDB0)

    ; Get address AMSDOS buffers
    LD   HL,(AMSDOS_MEMORY_POOL)    ; HL = Amsdos reserved area address (default is $A700)
    LD   DE,AMSDOS_CATALOG_BUFFER   ; Offset to the buffers
    ADD  HL,DE                      ; HL = Catalog & Sector Buffers (default is $A930)
    LD   (amsdos_buffers),HL

    ; Save "far address" of the overloaded AMSDOS RSXs
    CALL save_amsdos_rsxs_faraddress

.exit_init_workspace
    SCF
    RET

; ---------------------------------------------------------------------------
; Get address of CAS vectors in Amsdos ROM
; EXITS:
;    HL : Address CAS vectors
; ---------------------------------------------------------------------------
get_amsdos_cas_vectors
    ; Get the "far address" for RST 4 in patched CAS vectors
    LD   HL,(CAS_IN_OPEN + 1)       ; $A88B
    LD   E,(HL)
    INC  HL
    LD   D,(HL)                     ; DE -> Amsdos ROM routine ($CD30 CPC | $CD94 CPC+)
    INC  HL
    LD   C,(HL)                     ; C -> ROM Number (7)

.find_offset
    CALL ldrom_a_from_de            ; LD A,(DE) from ROM
    INC  DE
    CP   $11
    JR   NZ,.find_offset

    ; DE = $CD42
    CALL ldrom_a_from_de            ; LD A,(DE) from ROM
    LD   L,A
    INC  DE
    CALL ldrom_a_from_de            ; LD A,(DE) from ROM
    LD   H,A                        ; HL = $10D2
    LD   DE,CAS_IN_CLOSE            ; DE = $BC7A
    ADD  HL,DE                      ; HL = $CD4C
    RET

; ---------------------------------------------------------------------------
; Save the "far address" of the Amsdos RSXs that we are overloading
; (|DRIVE, |DIR, |ERA, |REN, $84, $85, $86).
; ---------------------------------------------------------------------------
save_amsdos_rsxs_faraddress
    LD   HL,farcall_amsdos_drive
    LD   (HL),'B' + $80             ; Search for |B
    CALL KL_FIND_COMMAND            ; The command name must be in RAM
    LD   A,C                        ; Get Amsdos ROM number

    LD   DE,farcall_amsdos_drive
    LD   BC,3
    ADD  HL,BC                      ; Skip |B
    EX   DE,HL

    CALL save_far_address           ; Save |DRIVE far address

    EX   DE,HL
    ADD  HL,BC                      ; Skip |USER
    EX   DE,HL
    
    ; Save |DIR, |ERA, |REN
    CALL save_3_far_address

    EX   DE,HL
    LD   BC,9
    ADD  HL,BC                      ; Skip ^A ($81),^B ($82), ^C ($83)
    EX   DE,HL

    ; Save |^D (Read Sector), |^E (Write Sector), |^F (Format Track)
save_3_far_address
    LD   B,3
.loop_save_3_far_address
    CALL save_far_address           ; Save far address
    DJNZ .loop_save_3_far_address
    RET

; ---------------------------------------------------------------------------
; Save far address in buffer
; ENTRIES:
;    HL : Buffer address
;    DE : RSX ROM address
;     A : ROM number
; ---------------------------------------------------------------------------
save_far_address
    LD   (HL),E
    INC  L
    LD   (HL),D                     ; ROM address
    INC  L
    LD   (HL),A                     ; ROM number
    INC  L
    INC  DE
    INC  DE
    INC  DE                         ; Update ROM pointer
    RET

; ---------------------------------------------------------------------------
; Read a byte from a ROM | LD A,(DE)
; ---------------------------------------------------------------------------
ldrom_a_from_de
    PUSH HL
    LD   HL,$C91A                   ; LD A,(DE) | RET
    PUSH HL
    LD   HL,0
    ADD  HL,SP
    CALL KL_FAR_PCHL                ; HL = Address | C = ROM Select
    POP  HL
    POP  HL
    RET

; ---------------------------------------------------------------------------
; Print a string finished in $FF using the firmware
; ENTRY:
;    HL : Pointer to the string
; ---------------------------------------------------------------------------
print_text
    LD   A,(HL)
.loop_print_text
    CALL TXT_OUTPUT
    INC  HL
    LD   A,(HL)
.continue_print_text
    CP   $FF
    JR   NZ,.loop_print_text
    RET

; Print_String Num_bytes,String
;    LD   A,(HL)
;    RET  Z
;    LD   B,A
;.loop_print_text
;    LD   A,(HL)
;    CALL TXT_OUTPUT
;    INC  HL
;    DJNZ .loop_print_text
;    RET

; ---------------------------------------------------------------------------
initialize_text
    DEFB $0F,2,' AMELIE v0.1 ',$A4,'2012 PulkoMandy & SyX',$0F,1,10,13,$FF

; ---------------------------------------------------------------------------
; Put after the Amsdos memory zone in $BE40 - $BE7D (Variables for Amélie)
; ---------------------------------------------------------------------------
begin_ameliedos_patch
    RORG AMSDOS_HOOK

; ---------------------------------------------------------------------------
; CAS vectors hook
hook_for_amsdos_cas_vectors
    RST  $18                        ; FAR_CALL amelie_hook
    DEFW amelie_cas_hook_far_call
    RET

amelie_cas_hook_far_call
    DEFW amelie_cas_hook            ; ROM Address
    DEFB 0                          ; ROM number for our ROM

; ---------------------------------------------------------------------------
; Amsdos variables
amsdos_cas_vectors
    DEFS 2                          ; Amsdos ROM CAS Vectors (CPC = $CD4C / CPC+ = $CDB0)

amsdos_buffers
    DEFS 2                          ; Amsdos reserved area + 560 
                                    ; Start of Catalog (128 bytes) and Sector (512) buffers
;AMSDOS_CATALOG_BUFFER           EQU $0230   ; (128) Buffer for Catalog Records
;AMSDOS_SECTOR_BUFFER            EQU $02B0   ; (512) Sector Buffer

; We should storage the pointer to the Temporary record and filename buffer, too.
; At least if we are going to use that buffer to decode the filenames.
; AMSDOS_RECORD_NAME_BUFFER       EQU $00E4   ; (128) Temporary Record & Filename Buffer
                                    
; ---------------------------------------------------------------------------
; Far address of overloaded RSXs
farcall_amsdos_drive
    DEFS 2                          ; |DRIVE RSX address
    DEFS 1                          ; |DRIVE RSX ROM number

farcall_amsdos_dir
    DEFS 2                          ; |DIR RSX address
    DEFS 1                          ; |DIR RSX ROM number

farcall_amsdos_era
    DEFS 2                          ; |ERA RSX address
    DEFS 1                          ; |ERA RSX ROM number

farcall_amsdos_ren
    DEFS 2                          ; |REN RSX address
    DEFS 1                          ; |REN RSX ROM number
 
farcall_amsdos_read_sector
    DEFS 2                          ; |^D  RSX address
    DEFS 1                          ; |^D RSX ROM number

farcall_amsdos_write_sector
    DEFS 2                          ; |^E RSX address
    DEFS 1                          ; |^E RSX ROM number

farcall_amsdos_format_track
    DEFS 2                          ; |^F RSX address
    DEFS 1                          ; |^F RSX ROM number

; ---------------------------------------------------------------------------
; SD Commands

; ---------------------------------------------------------------------------
    REND

; ---------------------------------------------------------------------------
end_ameliedos_patch

; --------------------------------------------------------------------------- 
; Padding the rom with 0s until the checksum byte
    ORG  $FFFF
checksum_byte
    DEFB 0

; ---------------------------------------------------------------------------
    END
