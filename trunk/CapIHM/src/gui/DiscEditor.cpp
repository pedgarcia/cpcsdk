#include "DiscEditor.h"

#include "emulator.h"

DiscEditorImpl::DiscEditorImpl( wxWindow* parent )
:
DiscEditor( parent )
{
	// Get the disk info.
	t_drive FloppyImage = Emulator::getInstance()->GetFDC().GetDriveA();
	// Fill in the Overview
	wxString s;
	s << FloppyImage.tracks;
	trackCount->SetValue(s);
	s.Empty();
	s << FloppyImage.sides;
	sideCount->SetValue(s);

	wxColour c;

	for(int side = 0; side <= FloppyImage.sides; side++) {
		c.Set(255,255,side*255);
		for(int row = 0; row < FloppyImage.tracks; row++) {
			t_track* currentTrack = &FloppyImage.track[row][side];
			int pos = 0;
			for(int col = 0;col < currentTrack->sectors; col++)
			{
				s.Empty();
				s << row << _(":") << col;
				wxGBPosition p(row,pos + side*40);
				wxButton* b = new wxButton(m_panel17, wxID_ANY, s);
				b->SetBackgroundColour(c);
				wxSize k(currentTrack->sector[col].size/16,8);
				b->SetMinSize(k);
				b->SetMaxSize(k);
				diskOverview->Add(b, p, wxGBSpan(1,currentTrack->sector[col].size/128), 0, 0);
				pos += currentTrack->sector[col].size/128;
			}
		}
	}
	diskOverview->Layout();
}
