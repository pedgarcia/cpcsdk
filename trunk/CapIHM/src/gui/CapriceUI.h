///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Sep 19 2008)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __CapriceUI__
#define __CapriceUI__

#include <wx/statusbr.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/frame.h>
#include <wx/checkbox.h>
#include <wx/toolbar.h>
#include <wx/listbook.h>
#include <wx/listctrl.h>
#include <wx/stattext.h>
#include <wx/spinctrl.h>
#include <wx/listbox.h>
#include <wx/textctrl.h>
#include <wx/notebook.h>
#include <wx/imaglist.h>
#include <wx/dialog.h>
#include <wx/statbmp.h>
#include <wx/statline.h>
#include <wx/statbox.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class CapriceWindow
///////////////////////////////////////////////////////////////////////////////
class CapriceWindow : public wxFrame 
{
	private:
	
	protected:
		wxStatusBar* m_statusBar1;
		wxMenuBar* m_menubar1;
		wxMenu* m_menu_file;
		wxMenu* m_menu_drivea;
		wxMenu* m_menu_driveb;
		wxMenu* m_menu8;
		wxMenu* m_menu3;
		wxMenu* m_menu2;
		wxMenuItem* m_menuItem_run;
		wxMenuItem* m_menuItem_pause;
		wxMenu* m_menu4;
		wxMenu* m_menu5;
		wxPanel* m_panel4;
		
		// Virtual event handlers, overide them in your derived class
		virtual void onExit1( wxCloseEvent& event ){ event.Skip(); }
		virtual void OnIdle( wxIdleEvent& event ){ event.Skip(); }
		virtual void onInsertDiscA( wxCommandEvent& event ){ event.Skip(); }
		virtual void onInsertDiscB( wxCommandEvent& event ){ event.Skip(); }
		virtual void onLoadSNA( wxCommandEvent& event ){ event.Skip(); }
		virtual void onSaveSNA( wxCommandEvent& event ){ event.Skip(); }
		virtual void onExit2( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnOpenConfigGeneral( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnFullScreen( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnReset( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnRun( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnPause( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnRegister( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnShowAssembler( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnAbout( wxCommandEvent& event ){ event.Skip(); }
		virtual void windowKeyDown( wxKeyEvent& event ){ event.Skip(); }
		virtual void windowKeyUp( wxKeyEvent& event ){ event.Skip(); }
		
	
	public:
		CapriceWindow( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("CapriceReloaded"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxCAPTION|wxCLOSE_BOX|wxMINIMIZE_BOX|wxSYSTEM_MENU|wxTAB_TRAVERSAL, const wxString& name = wxT("CapriceMainWindow") );
		~CapriceWindow();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class DiscEditor
///////////////////////////////////////////////////////////////////////////////
class DiscEditor : public wxDialog 
{
	private:
	
	protected:
		wxNotebook* m_notebook2;
		wxPanel* m_panel1;
		wxToolBar* m_toolBar1;
		wxCheckBox* m_checkBox1;
		wxCheckBox* m_checkBox2;
		wxListbook* m_listbook1;
		wxPanel* m_panel2;
		wxToolBar* m_toolBar3;
		wxStaticText* m_staticText23;
		wxSpinCtrl* m_spinCtrl1;
		wxStaticText* m_staticText24;
		wxListBox* m_listBox1;
		wxTextCtrl* m_textCtrl78;
	
	public:
		DiscEditor( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Disc Editor"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 643,345 ), long style = wxDEFAULT_DIALOG_STYLE );
		~DiscEditor();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class FileProperties
///////////////////////////////////////////////////////////////////////////////
class FileProperties : public wxDialog 
{
	private:
	
	protected:
		wxStaticBitmap* m_bitmap2;
		wxTextCtrl* m_textCtrl80;
		wxStaticLine* m_staticline1;
		wxStaticText* m_staticText26;
		wxStaticText* m_staticText27;
		wxStaticLine* m_staticline2;
	
	public:
		FileProperties( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Properties"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 411,367 ), long style = wxDEFAULT_DIALOG_STYLE );
		~FileProperties();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class CapriceAbout
///////////////////////////////////////////////////////////////////////////////
class CapriceAbout : public wxDialog 
{
	private:
	
	protected:
		wxStaticBitmap* m_bitmap2;
		wxStaticText* m_staticText8;
		wxStaticText* m_staticText9;
		wxStaticText* m_staticText5;
		wxStaticText* m_staticText10;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnAboutClose( wxCloseEvent& event ){ event.Skip(); }
		
	
	public:
		CapriceAbout( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("About CapriceReloaded"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE );
		~CapriceAbout();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class RegistersStates
///////////////////////////////////////////////////////////////////////////////
class RegistersStates : public wxDialog 
{
	private:
	
	protected:
		wxNotebook* m_nb_Register;
		wxPanel* m_panel4;
		wxStaticText* m_staticText9;
		wxStaticText* m_staticText10;
		wxStaticText* m_staticText11;
		wxStaticText* m_staticText12;
		wxTextCtrl* m_tCrA;
		wxTextCtrl* m_tCrAx;
		wxStaticText* m_staticText13;
		wxTextCtrl* m_tCrF;
		wxTextCtrl* m_tCrFx;
		wxStaticText* m_staticText14;
		wxTextCtrl* m_tCrB;
		wxTextCtrl* m_tCrBx;
		wxStaticText* m_staticText15;
		wxTextCtrl* m_tCrC;
		wxTextCtrl* m_tCrCx;
		wxStaticText* m_staticText16;
		wxTextCtrl* m_tCrD;
		wxTextCtrl* m_tCrDx;
		wxStaticText* m_staticText17;
		wxTextCtrl* m_tCrE;
		wxTextCtrl* m_tCrEx;
		wxStaticText* m_staticText18;
		wxTextCtrl* m_tCrH;
		wxTextCtrl* m_tCrHx;
		wxStaticText* m_staticText19;
		wxTextCtrl* m_tCrL;
		wxTextCtrl* m_tCrLx;
		wxStaticText* m_staticText31;
		wxTextCtrl* m_tCrI;
		wxStaticText* m_staticText32;
		wxStaticText* m_staticText33;
		wxTextCtrl* m_tCrR;
		wxStaticText* m_staticText21;
		wxStaticText* m_staticText22;
		wxStaticText* m_staticText23;
		wxStaticText* m_staticText24;
		wxTextCtrl* m_tCrBC;
		wxTextCtrl* m_tCrBCx;
		wxStaticText* m_staticText25;
		wxTextCtrl* m_tCrDE;
		wxTextCtrl* m_tCrDEx;
		wxStaticText* m_staticText26;
		wxTextCtrl* m_tCrHL;
		wxTextCtrl* m_tCrHLx;
		wxStaticText* m_staticText27;
		wxTextCtrl* m_tCrIX;
		wxStaticText* m_staticText45;
		wxStaticText* m_staticText28;
		wxTextCtrl* m_tCrIY;
		wxStaticText* m_staticText44;
		wxStaticText* m_staticText29;
		wxTextCtrl* m_tCrPC;
		wxStaticText* m_staticText43;
		wxStaticText* m_staticText30;
		wxTextCtrl* m_tCrSP;
		wxStaticText* m_staticText34;
		wxStaticText* m_staticText35;
		wxStaticText* m_staticText36;
		wxStaticText* m_staticText37;
		wxStaticText* m_staticText38;
		wxStaticText* m_staticText39;
		wxStaticText* m_staticText40;
		wxStaticText* m_staticText41;
		wxCheckBox* m_cB_SFlags;
		wxCheckBox* m_cB_ZFlags;
		wxCheckBox* m_cB_HFlags;
		wxCheckBox* m_cB_PFlags;
		wxCheckBox* m_cB_NFlags;
		wxCheckBox* m_cB_CFlags;
		wxStaticText* m_staticText42;
		wxCheckBox* m_cB_SFlagsShadow;
		wxCheckBox* m_cB_ZFlagsShadow;
		wxCheckBox* m_cB_HFlagsShadow;
		wxCheckBox* m_cB_PFlagsShadow;
		wxCheckBox* m_cB_NFlagsShadow;
		wxCheckBox* m_cB_CFlagsShadow;
		wxCheckBox* m_checkBox15;
		wxCheckBox* m_checkBox16;
		wxPanel* m_panel8;
		wxStaticText* m_staticText46;
		wxTextCtrl* m_tCcHCC;
		wxStaticText* m_staticText47;
		wxTextCtrl* m_tCcVCC;
		wxStaticText* m_staticText48;
		wxTextCtrl* m_tCcVLA;
		wxStaticText* m_staticText49;
		wxTextCtrl* m_tCcVLC;
		wxStaticText* m_staticText50;
		wxTextCtrl* m_tCcR0;
		wxStaticText* m_staticText51;
		wxTextCtrl* m_tCcR1;
		wxStaticText* m_staticText52;
		wxTextCtrl* m_tCcR2;
		wxStaticText* m_staticText53;
		wxTextCtrl* m_tCcR3;
		wxStaticText* m_staticText54;
		wxTextCtrl* m_tCcR4;
		wxStaticText* m_staticText55;
		wxTextCtrl* m_tCcR5;
		wxStaticText* m_staticText56;
		wxTextCtrl* m_tCcR6;
		wxStaticText* m_staticText57;
		wxTextCtrl* m_tCcR7;
		wxStaticText* m_staticText58;
		wxTextCtrl* m_tCcR9;
		wxStaticText* m_staticText59;
		wxStaticText* m_sT_HLineLength;
		wxCheckBox* m_cB_HLineLengthIsOk;
		wxStaticText* m_staticText61;
		wxStaticText* m_sT_VFrameLength;
		wxCheckBox* m_cB_VFrameLengthIsOk;
		wxPanel* m_panel9;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnCloseR( wxCloseEvent& event ){ event.Skip(); }
		virtual void OnIdleR( wxIdleEvent& event ){ event.Skip(); }
		virtual void OnInitR( wxInitDialogEvent& event ){ event.Skip(); }
		virtual void OnKillFocusA( wxFocusEvent& event ){ event.Skip(); }
		virtual void OnSetFocusA( wxFocusEvent& event ){ event.Skip(); }
		virtual void OnKillFocusAx( wxFocusEvent& event ){ event.Skip(); }
		virtual void OnSetFocusAx( wxFocusEvent& event ){ event.Skip(); }
		virtual void OnKillFocusF( wxFocusEvent& event ){ event.Skip(); }
		virtual void OnSetFocusF( wxFocusEvent& event ){ event.Skip(); }
		virtual void OnKillFocusFx( wxFocusEvent& event ){ event.Skip(); }
		virtual void OnSetFocusFx( wxFocusEvent& event ){ event.Skip(); }
		virtual void OnKillFocusB( wxFocusEvent& event ){ event.Skip(); }
		virtual void OnSetFocusB( wxFocusEvent& event ){ event.Skip(); }
		virtual void OnKillFocusBx( wxFocusEvent& event ){ event.Skip(); }
		virtual void OnSetFocusBx( wxFocusEvent& event ){ event.Skip(); }
		virtual void OnKillFocusC( wxFocusEvent& event ){ event.Skip(); }
		virtual void OnSetFocusC( wxFocusEvent& event ){ event.Skip(); }
		virtual void OnKillFocusCx( wxFocusEvent& event ){ event.Skip(); }
		virtual void OnSetFocusCx( wxFocusEvent& event ){ event.Skip(); }
		virtual void OnKillFocusD( wxFocusEvent& event ){ event.Skip(); }
		virtual void OnSetFocusD( wxFocusEvent& event ){ event.Skip(); }
		virtual void OnKillFocusDx( wxFocusEvent& event ){ event.Skip(); }
		virtual void OnSetFocusDx( wxFocusEvent& event ){ event.Skip(); }
		virtual void OnKillFocusE( wxFocusEvent& event ){ event.Skip(); }
		virtual void OnSetFocusE( wxFocusEvent& event ){ event.Skip(); }
		virtual void OnKillFocusEx( wxFocusEvent& event ){ event.Skip(); }
		virtual void OnSetFocusEx( wxFocusEvent& event ){ event.Skip(); }
		virtual void OnKillFocusH( wxFocusEvent& event ){ event.Skip(); }
		virtual void OnSetFocusH( wxFocusEvent& event ){ event.Skip(); }
		virtual void OnKillFocusHx( wxFocusEvent& event ){ event.Skip(); }
		virtual void OnSetFocusHx( wxFocusEvent& event ){ event.Skip(); }
		virtual void OnKillFocusL( wxFocusEvent& event ){ event.Skip(); }
		virtual void OnSetFocusL( wxFocusEvent& event ){ event.Skip(); }
		virtual void OnKillFocusLx( wxFocusEvent& event ){ event.Skip(); }
		virtual void OnSetFocusLx( wxFocusEvent& event ){ event.Skip(); }
		virtual void OnKillFocusI( wxFocusEvent& event ){ event.Skip(); }
		virtual void OnSetFocusI( wxFocusEvent& event ){ event.Skip(); }
		virtual void OnKillFocusR( wxFocusEvent& event ){ event.Skip(); }
		virtual void OnSetFocusR( wxFocusEvent& event ){ event.Skip(); }
		virtual void OnKillFocusHCC( wxFocusEvent& event ){ event.Skip(); }
		virtual void OnSetFocusHCC( wxFocusEvent& event ){ event.Skip(); }
		virtual void OnKillFocusVCC( wxFocusEvent& event ){ event.Skip(); }
		virtual void OnSetFocusVCC( wxFocusEvent& event ){ event.Skip(); }
		virtual void OnKillFocusVLA( wxFocusEvent& event ){ event.Skip(); }
		virtual void OnSetFocusVLA( wxFocusEvent& event ){ event.Skip(); }
		virtual void OnKillFocusVLC( wxFocusEvent& event ){ event.Skip(); }
		virtual void OnSetFocusVLC( wxFocusEvent& event ){ event.Skip(); }
		virtual void OnKillFocusR0( wxFocusEvent& event ){ event.Skip(); }
		virtual void OnSetFocusR0( wxFocusEvent& event ){ event.Skip(); }
		virtual void OnTextR0( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnTextEnterR0( wxCommandEvent& event ){ event.Skip(); }
		virtual void OnKillFocusR1( wxFocusEvent& event ){ event.Skip(); }
		virtual void OnSetFocusR1( wxFocusEvent& event ){ event.Skip(); }
		virtual void OnKillFocusR2( wxFocusEvent& event ){ event.Skip(); }
		virtual void OnSetFocusR2( wxFocusEvent& event ){ event.Skip(); }
		virtual void OnKillFocusR3( wxFocusEvent& event ){ event.Skip(); }
		virtual void OnSetFocusR3( wxFocusEvent& event ){ event.Skip(); }
		virtual void OnKillFocusR4( wxFocusEvent& event ){ event.Skip(); }
		virtual void OnSetFocusR4( wxFocusEvent& event ){ event.Skip(); }
		virtual void OnKillFocusR5( wxFocusEvent& event ){ event.Skip(); }
		virtual void OnSetFocusR5( wxFocusEvent& event ){ event.Skip(); }
		virtual void OnKillFocusR6( wxFocusEvent& event ){ event.Skip(); }
		virtual void OnSetFocusR6( wxFocusEvent& event ){ event.Skip(); }
		virtual void OnKillFocusR7( wxFocusEvent& event ){ event.Skip(); }
		virtual void OnSetFocusR7( wxFocusEvent& event ){ event.Skip(); }
		virtual void OnKillFocusR9( wxFocusEvent& event ){ event.Skip(); }
		virtual void OnSetFocusR9( wxFocusEvent& event ){ event.Skip(); }
		
	
	public:
		RegistersStates( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Registers States"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE );
		~RegistersStates();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class Memory
///////////////////////////////////////////////////////////////////////////////
class Memory : public wxDialog 
{
	private:
	
	protected:
	
	public:
		Memory( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Memory"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );
		~Memory();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class ConfigDialog
///////////////////////////////////////////////////////////////////////////////
class ConfigDialog : public wxDialog 
{
	private:
	
	protected:
		wxNotebook* m_notebook3;
		wxPanel* m_panel7;
		wxStaticText* m_staticText62;
		wxTextCtrl* m_textCtrl44;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnCloseC( wxCloseEvent& event ){ event.Skip(); }
		
	
	public:
		ConfigDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Configuration"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );
		~ConfigDialog();
	
};

#endif //__CapriceUI__
