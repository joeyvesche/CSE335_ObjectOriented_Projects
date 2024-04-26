/**
 * @file TimelineDlg.h
 * @author joeyv
 *
 *
 */

#ifndef CANADIANEXPERIENCE_TIMELINEDLG_H
#define CANADIANEXPERIENCE_TIMELINEDLG_H

class Timeline;

/**
 * Timeline dialog box
 */
class TimelineDlg final : public wxDialog {
private:
    /// The timeline we are editing
    Timeline* mTimeline = nullptr;

    /// Number of frames in the animation
    int mNumberOfFrames;

    /// Frame rate in the animation
    int mFrameRate;

public:
    TimelineDlg(wxWindow* parent, Timeline* timeline);
    void OnOK(wxCommandEvent& event);

};

#endif //CANADIANEXPERIENCE_TIMELINEDLG_H
