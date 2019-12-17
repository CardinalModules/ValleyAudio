#ifndef TFORM_EDITOR_MENU_ROWS
#define TFORM_EDITOR_MENU_ROWS
#include "../../Valley.hpp"
#include "../../ValleyComponents.hpp"
#include "TFormEditorButton.hpp"
#include "TFormEditorNumberChoice.hpp"
#include "TFormEditorGrid.hpp"
#include "WaveDisplay.hpp"

#define TFORM_EDITOR_COLS 8
#define TFORM_EDITOR_ROWS 8
#define TFORM_EDITOR_SLOTS TFORM_EDITOR_ROWS * TFORM_EDITOR_COLS

struct TFormMenuRow : OpaqueWidget {
    const int buttonWidth = 44;
    const int buttonHeight = 15;
    const int buttonOffset = 3;
    std::shared_ptr<Font> font;

    TFormMenuRow();
};

struct TFormBankEditMainRow : TFormMenuRow {
    TFormEditorButton* loadButton;
    TFormEditorButton* copyButton;
    TFormEditorButton* pasteButton;
    TFormEditorButton* clearButton;
    TFormEditorButton* purgeButton;
    TFormEditorButton* viewButton;
    TFormEditorButton* backButton;
    TFormEditorGrid<TFORM_EDITOR_ROWS, TFORM_EDITOR_COLS>* grid;
    TFormEditorButtonStyle emptySlotButtonStyles[NUM_BUTTON_MODES];
    TFormEditorButtonStyle filledSlotButtonStyles[NUM_BUTTON_MODES];

    std::shared_ptr<std::vector<bool>> slotFilled;
    std::shared_ptr<int> selectedBank;
    bool selectedBankIsFilled;

    TFormBankEditMainRow();
    void step() override;
    void draw(const DrawArgs& args) override;
    void setSlotFilledFlag(int slot, bool isFilled);
};

struct TFormClearRow : TFormMenuRow {
    TFormEditorButton* yesButton;
    TFormEditorButton* noButton;
    std::shared_ptr<int> selectedBank;

    TFormClearRow();
    void draw(const DrawArgs& args) override;
};

struct TFormBankEditPurgeRow : TFormMenuRow {
    TFormEditorButton* yesButton;
    TFormEditorButton* noButton;
    std::shared_ptr<int> selectedBank;

    TFormBankEditPurgeRow();
    void draw(const DrawArgs& args) override;
};

struct TFormBankEditCopyRow : TFormMenuRow {
    TFormEditorButton* cancelButton;
    TFormEditorButton* pasteButton;
    TFormEditorNumberChoice* startWave;
    TFormEditorNumberChoice* endWave;
    TFormEditorGrid<TFORM_EDITOR_ROWS, TFORM_EDITOR_COLS>* grid;
    int destBank;

    TFormBankEditCopyRow();
    void draw(const DrawArgs& args) override;
};

struct TFormWaveViewPane : TFormMenuRow {
    TFormEditorWaveDisplay* waveDisplay;
    TFormEditorButton* backButton;
    NVGcolor waveLineColor;
    NVGcolor waveFillColor;
    float waveSliderPos;
    std::shared_ptr<int> selectedBank;
    int selectedWave = 0;

    //float waveData[TFORM_MAX_NUM_WAVES][TFORM_MAX_WAVELENGTH];
    std::vector<std::vector<float>> waveData;

    TFormWaveViewPane();
    void draw(const DrawArgs& args) override;
    void step() override;
    void onDragMove(const event::DragMove& e) override;
};

#endif
