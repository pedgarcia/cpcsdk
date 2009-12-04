//
// Caprice32 GateArray memory emulator
//

#pragma once
#ifndef _MEMORY_H_
#define _MEMORY_H_

#include "cap32type.h"

class t_CPC;

class t_Memory
{
private:
	t_CPC&			CPC;
	
	unsigned char	ROM_config;
	unsigned char	RAM_bank;
	unsigned char	RAM_config;
	unsigned char	upper_ROM;

	byte*			membank_config[8][4];

  //RAM pointer
	byte*			pbRAM;
  //Low ROM
	byte*			pbROMlo;
  //High ROM
	byte*			pbROMhi;
  //Expension ROM
	byte*			pbExpansionROM;

	byte*			membank_read[4];
	byte*			membank_write[4];
	byte*			memmap_ROM[256];

public:
	//! Default constructor
	t_Memory(t_CPC &cpc);

	void Clean();
	void Reset(bool MF2reset);

	int Init();
	void InitMemConfig();

	bool UpdateRAMSize(unsigned int size);

	char* GetROMFile(unsigned int idx) const;

	int getTypeForAddress(word adr)
	{
		if(membank_read[adr>>14] == pbROMlo)
			return 1;
		else if(membank_read[adr>>14] == pbROMhi)
			return 2;
		else if(membank_read[adr>>14] == pbExpansionROM)
			return 4;
		return 0;
	}

  /**
   * Return the RAM pointer
   */
	inline byte*			GetRAM() const						{ return pbRAM;				}
	inline byte*			GetROMLow() const					{ return pbROMlo;			}
	inline byte*			GetROMHigh() const					{ return pbROMhi;			}
	inline byte*			GetROMExpansion() const				{ return pbExpansionROM;	}
	
	inline void				SetROMLow(byte* m)					{ pbROMlo = m;				}
	inline void				SetROMHigh(byte* m)					{ pbROMhi = m;				}
	inline void				SetROMExpansion(byte* m)			{ pbExpansionROM = m;		}

	inline unsigned char	GetROMConfig() const				{ return ROM_config;		}
	inline void				SetROMConfig(unsigned char v)		{ ROM_config = v;			}
	inline unsigned char	GetRAMBank() const					{ return RAM_bank;			}
	inline void				SetRAMBank(unsigned char v)			{ RAM_bank = v;				}
	inline unsigned char	GetRAMConfig() const				{ return RAM_config;		}
	inline void				SetRAMConfig(unsigned char v)		{ RAM_config = v;			}
	inline unsigned char	GetUpperROM() const					{ return upper_ROM;			}
	
	
	void SetUpperROM(unsigned char v);

	void ga_init_banking (void);
	void ga_memory_manager (void);

	inline byte Read(word addr) 
	{
		return (*(membank_read[addr >> 14] + (addr & 0x3fff))); // returns a byte from a 16KB memory bank
	}

	inline void Write(word addr, byte val) 
	{
		*(membank_write[addr >> 14] + (addr & 0x3fff)) = val; // writes a byte to a 16KB memory bank
	}


protected:
	int emulator_patch_ROM();

	int RAMInit();
	int ROMInit();
};
#endif
