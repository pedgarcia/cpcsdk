#pragma once
#include <map>
#include "CapriceUI.h"
#include <wx/stdpaths.h>
#include <wx/string.h>

class Emulator;

class CapriceInputSettingsImpl : public InputSettings
{
	public:
		CapriceInputSettingsImpl(wxWindow* WinID);
		~CapriceInputSettingsImpl();
		void applySettings();

	private:
		virtual void onKeyClick(wxCommandEvent& event);
		virtual void onKeyPress(wxKeyEvent& event);
		virtual void onSave(wxCommandEvent& event);
		virtual void applySettings(wxCommandEvent& event) { applySettings(); }
		virtual void changeCRTCType( wxSpinEvent& event );
		virtual void changeColorPalette( wxCommandEvent& event );

		void saveKeymap();

		wxString keyCodeToName(int keycode);

		/**
		 * Returns the name of the keyboard configuration file
		 * @TODO Find the real file to use between share directory or user
		 */

		const char * getKeymapFileNameLoad();
		/**
		 * Returns the name of the keyboard configuration file
		 * @TODO Find the real file to use between directory or user
		 */
		const char * getKeymapFileNameSave();


		Emulator& emulator;

		typedef struct{
			int stdKeyCode;
			int shiftKeyCode;
			int ctrlKeyCode;
		} CPC_Key;

		//typedef std::map<uint16_t, CPC_Key> CPC_Keymap;
		typedef std::map<unsigned short, CPC_Key> CPC_Keymap;
		CPC_Keymap keymap;
		CPC_Keymap::iterator iter;

		wxButton* lastClickedButton;
};
