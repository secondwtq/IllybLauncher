//
// Created by secondwtq <lovejay-lovemusic@outlook.com> 2015/05/25.
// Copyright (c) 2015 SCU ISDC All rights reserved.
//
// This file is part of ISDCNext.
//
// We have always treaded the borderland.
//

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class IllybLauncher : public wxApp {

    public:

    virtual bool OnInit();

};

class IllybMainFrame : public wxFrame {

    public:

    IllybMainFrame();

    void OnPaint(wxPaintEvent& WXUNUSED(event));

    private:

    wxBitmap m_background;

    wxDECLARE_EVENT_TABLE();

};

class IllybButton : public wxButton {

    public:

    IllybButton(wxWindow *parent, wxWindowID id, const wxString& label = wxEmptyString,
                const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize,
                long style = wxSIMPLE_BORDER, const wxValidator& validator = wxDefaultValidator,
                const wxString& name = wxButtonNameStr) :
            wxButton(parent, id, label, pos, size, style, validator, name) { }

    void OnPaint(wxPaintEvent& evt);
    void OnMouseDown(wxMouseEvent& evt);
    void OnMouseReleased(wxMouseEvent& evt);
    void OnMouseLeft(wxMouseEvent& evt);

    void render(wxDC& dc);
    void rerender();

    bool pressed = false;

    DECLARE_EVENT_TABLE();

};

//class IllybTransPanel : public wxPanel {
//
//    public:
//
//    IllybTransPanel(wxWindow *parent) : wxPanel(parent) { }
//
//    void OnPaint(wxPaintEvent &evt);
//
//    DECLARE_EVENT_TABLE();
//
//};

enum {
    ILLBD_Initial = 0
};

wxBEGIN_EVENT_TABLE(IllybMainFrame, wxFrame)
    EVT_PAINT(IllybMainFrame::OnPaint)
wxEND_EVENT_TABLE()

//wxBEGIN_EVENT_TABLE(IllybTransPanel, wxPanel)
//    EVT_PAINT(IllybTransPanel::OnPaint)
//wxEND_EVENT_TABLE();

wxBEGIN_EVENT_TABLE(IllybButton, wxButton)
    EVT_PAINT(IllybButton::OnPaint)
    EVT_LEFT_DOWN(IllybButton::OnMouseDown)
    EVT_LEFT_UP(IllybButton::OnMouseReleased)
    EVT_LEAVE_WINDOW(IllybButton::OnMouseLeft)
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(IllybLauncher);

void IllybButton::rerender() {
    wxClientDC dc(this);
    this->render(dc);
}

void IllybButton::OnMouseDown(wxMouseEvent& evt) {
    this->pressed = true;
    rerender(); }

void IllybButton::OnMouseLeft(wxMouseEvent& evt) {
    this->pressed = false;
    rerender(); }

void IllybButton::OnMouseReleased(wxMouseEvent& evt) {
    this->pressed = false;
    rerender(); }

void IllybButton::render(wxDC &dc) {

    wxRect rect = this->GetClientRect();
    rect.Deflate(1);

//    wxRect grid_rect = rect;
//    grid_rect.SetHeight(grid_rect.GetHeight() / 1.5);
//    dc.GradientFillLinear(grid_rect, wxColour(0, 0, 0, 128), wxColour(0, 0, 0, 0), wxSOUTH);

    dc.SetBrush(wxBrush(wxColor(16, 16, 16)));
    if (!this->pressed)
        dc.SetPen(wxPen(wxColor(202, 42, 32), 2));
    else
        dc.SetPen(wxPen(wxColor(142, 32, 24), 1));

    if (!this->pressed)
        dc.SetTextForeground(*wxWHITE);
    else
        dc.SetTextForeground(*wxYELLOW);
    dc.DrawRoundedRectangle(rect, 3);
    dc.DrawLabel("CLOSE", wxNullBitmap, rect, wxALIGN_CENTER);
}

void IllybButton::OnPaint(wxPaintEvent &evt) {
    wxPaintDC dc(this);
    this->render(dc);
}

bool IllybLauncher::OnInit() {
    if (!wxApp::OnInit()) return false;

    IllybMainFrame *main_frame = new IllybMainFrame();
    main_frame->CenterOnScreen();
    main_frame->Show(true);

    return true;
}

void IllybMainFrame::OnPaint(wxPaintEvent& WXUNUSED(event)) {
    wxPaintDC dc(this);

    dc.Clear();
    const wxSize size = GetClientSize();
    dc.DrawBitmap(m_background, dc.DeviceToLogicalX(0),
                  dc.DeviceToLogicalY(0), false);
//    gc->DrawBitmap(m_background, 0, 0, size.x, size.y);
}

//void IllybTransPanel::OnPaint(wxPaintEvent& evt) {
//    wxPaintDC dc(this);
//}

IllybMainFrame::IllybMainFrame()
        : wxFrame(NULL, wxID_ANY, wxT("Illyb Launcher by secondwtq"), wxPoint(0, 0), wxSize(800, 600),
                  wxSYSTEM_MENU | wxCLIP_CHILDREN) {

    wxMenuBar *menu_bar = new wxMenuBar;
    this->SetMenuBar(menu_bar);

//    this->CreateStatusBar();

    // this->SetBackgroundColour("#3b2422");

    wxBoxSizer *sizer_main = new wxBoxSizer(wxHORIZONTAL);
    this->SetSizer(sizer_main);

    wxBoxSizer *sizer_left = new wxBoxSizer(wxVERTICAL);
//    sizer_main->Add(sizer_left, 1, wxEXPAND | wxLEFT | wxTOP | wxBOTTOM, 7);

    wxPNGHandler *handler = new wxPNGHandler;
    wxImage::AddHandler(handler);

    m_background.LoadFile(wxT("background.png"), wxBITMAP_TYPE_PNG);

    wxBoxSizer *sizer_right = new wxBoxSizer(wxVERTICAL);

    wxPanel *panel_upper = new wxPanel(this, wxID_ANY, wxPoint(-1, -1),
            wxSize(-1, -1), wxBG_STYLE_TRANSPARENT | wxTRANSPARENT_WINDOW);
    sizer_right->Add(panel_upper, 1, wxEXPAND | wxALL, 0);
    wxBoxSizer *panel_upper_inner_sizer = new wxBoxSizer(wxVERTICAL);
    wxFlexGridSizer *sizer_owners = new wxFlexGridSizer(8, 4, 10, 10);
    panel_upper->SetSizer(panel_upper_inner_sizer);
    wxPanel *panel_upper_inner = new wxPanel(panel_upper, wxID_ANY, wxPoint(-1, -1),
                                             wxSize(-1, -1), wxBG_STYLE_TRANSPARENT | wxTRANSPARENT_WINDOW);
    panel_upper_inner_sizer->Add(panel_upper_inner, 1, wxEXPAND | wxALL, 10);
    panel_upper_inner->SetSizer(sizer_owners);
    sizer_owners->AddGrowableCol(0, 1);
    sizer_owners->AddGrowableCol(1, 1);

    for (size_t i = 0; i < 8; i++) {
        wxTextCtrl *text_player = new wxTextCtrl(panel_upper_inner, wxID_ANY);
        wxComboBox *combo_owner = new wxComboBox(panel_upper_inner, wxID_ANY);
        wxComboBox *combo_loc = new wxComboBox(panel_upper_inner, wxID_ANY);
        wxComboBox *combo_alli = new wxComboBox(panel_upper_inner, wxID_ANY);

        combo_loc->SetMaxSize(wxSize(50, -1));
        combo_alli->SetMaxSize(wxSize(50, -1));

        combo_loc->SetMaxLength(1);

        sizer_owners->Add(text_player, 1, wxEXPAND);
        sizer_owners->Add(combo_owner, 1, wxEXPAND);
        sizer_owners->Add(combo_loc, 1);
        sizer_owners->Add(combo_alli, 1);
    }

    wxPanel *panel_btns = new wxPanel(this, wxID_ANY, wxPoint(-1, -1),
                                      wxSize(-1, -1), wxBG_STYLE_TRANSPARENT | wxTRANSPARENT_WINDOW);
    sizer_right->Add(panel_btns, 0, wxALIGN_BOTTOM | wxBOTTOM | wxALIGN_CENTER_HORIZONTAL |
            wxEXPAND, 0);
    wxBoxSizer *sizer_panel_btns = new wxBoxSizer(wxHORIZONTAL);
    panel_btns->SetSizer(sizer_panel_btns);


    wxButton *btn_close = new IllybButton(panel_btns, wxID_ANY, wxT("CLOSE"));
    wxButton *btn_start = new wxButton(panel_btns, wxID_ANY, wxT("START"));
    sizer_panel_btns->AddStretchSpacer();
    sizer_panel_btns->Add(btn_close, 0, wxTOP, 6);
    sizer_panel_btns->AddStretchSpacer();
    sizer_panel_btns->Add(btn_start, 0, wxTOP, 6);
    sizer_panel_btns->AddStretchSpacer();

    sizer_main->Add(sizer_right, 1, wxEXPAND | wxALL, 7);

    this->Layout();

}
