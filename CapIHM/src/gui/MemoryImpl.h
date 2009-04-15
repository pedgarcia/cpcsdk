#include "CapriceUI.h"
#include "emulator.h"

class MemoryImpl: public Memory
{
	private:
		Emulator* _emulator;
	protected:
		void RefreshMem (wxScrollEvent& event);
	public:
		MemoryImpl(wxWindow* parent, Emulator* emulator);
		~MemoryImpl();
};

