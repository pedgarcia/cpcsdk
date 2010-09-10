#ifndef __DiscEditor__
#define __DiscEditor__

/**
@file
Subclass of DiscEditor, which is generated by wxFormBuilder.
*/

#include "CapriceUI.h"
#include "fdc_old.h"

/** Implementing DiscEditor */
class DiscEditorImpl : public DiscEditor
{
	private:
		t_drive& FloppyImage;
		int currentTrack;
	public:
		/** Constructor */
		DiscEditorImpl( wxWindow* parent, int drive );
		void setTrack( wxSpinEvent& event );
		void setSector( wxCommandEvent& event );
		static t_sector* sectorClipboard;
	protected:
		void cutSector( wxCommandEvent& event );
		void copySector( wxCommandEvent& event );
		void pasteSector( wxCommandEvent& event );
		void deleteSector( wxCommandEvent& event );
		void renameSector( wxCommandEvent& event );

		void drawSectorExplorer( wxPaintEvent& event );
		void sectorLeftClick( wxMouseEvent& event );
};

#endif // __DiscEditor__
