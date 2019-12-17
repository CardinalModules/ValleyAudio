#ifndef TFORM_EDITOR_GRID_HPP
#define TFORM_EDITOR_GRID_HPP
#include "../../Valley.hpp"
#include "../../ValleyComponents.hpp"
#include "TFormEditorButton.hpp"

template<const int NRows, const int NCols>
struct TFormEditorGrid : OpaqueWidget {
    NVGcolor color;
    TFormEditorStyles style;
    TFormEditorButtonStyle buttonStyles[NUM_BUTTON_MODES];
    TFormEditorButton* slotButton[NRows][NCols];
    int selectedBank;

    TFormEditorGrid() {
        color = nvgRGB(0xAF, 0xAF, 0xAF);
        box.size = Vec(238, 155);

        buttonStyles[IDLE_MODE] = TFormEditorButtonStyle(nvgRGB(0xCF, 0xCF, 0xCF), nvgRGB(0x17, 0x17, 0x17), nvgRGBA(0x00, 0x00, 0x00, 0x00));
        buttonStyles[HOVER_MODE] = TFormEditorButtonStyle(nvgRGB(0xFF, 0xFF, 0xFF), nvgRGB(0x32, 0x32, 0x7F), nvgRGBA(0x00, 0x00, 0x00, 0x00));
        buttonStyles[HIGHLIGHT_MODE] =  TFormEditorButtonStyle(nvgRGB(0xFF, 0xFF, 0xFF), nvgRGB(0x6F, 0x6F, 0xEF), nvgRGBA(0x00, 0x00, 0x00, 0x00));
        buttonStyles[HIGHLIGHT_HOVER_MODE] = TFormEditorButtonStyle(nvgRGB(0xFF, 0xFF, 0xFF), nvgRGB(0x6F, 0x6F, 0xEF), nvgRGBA(0x00, 0x00, 0x00, 0x00));

        Vec slotButtonPos;
        float slotButtonWidth = box.size.x / NCols;
        float slotButtonHeight = box.size.y / NRows;
        for(int row = 0; row < NRows; ++row) {
            for(int col = 0; col < NCols; ++col) {

                slotButtonPos = Vec(col * slotButtonWidth, row * slotButtonHeight);
                slotButton[row][col] = createWidget<TFormEditorButton>(slotButtonPos);
                slotButton[row][col]->box.size.x = slotButtonWidth;
                slotButton[row][col]->box.size.y = slotButtonHeight;

                for(int m = 0; m < NUM_BUTTON_MODES; ++m) {
                    slotButton[row][col]->buttonStyles[m] = buttonStyles[m];
                }
                slotButton[row][col]->mode = IDLE_MODE;
                addChild(slotButton[row][col]);
            }
        }
    }

    void draw(const DrawArgs& args) override {
        Widget::draw(args);

        auto drawVSeparator = [=](float x, float height) {
            nvgBeginPath(args.vg);
            nvgMoveTo(args.vg, x, 0);
            nvgLineTo(args.vg, x, height);
            nvgStrokeWidth(args.vg, 1.0);
            nvgStrokeColor(args.vg, color);
            nvgStroke(args.vg);
        };

        auto drawHSeparator = [=](float y) {
            nvgBeginPath(args.vg);
            nvgMoveTo(args.vg, 0, y);
            nvgLineTo(args.vg, box.size.x, y);
            nvgStrokeWidth(args.vg, 1.0);
            nvgStrokeColor(args.vg, color);
            nvgStroke(args.vg);
        };

        float gridHeight = box.size.y;
        for(int i = 0; i < NCols + 1; ++i) {
            drawVSeparator(i * (box.size.x / NCols), gridHeight);
        }

        for(int i = 0; i < NRows + 1; ++i) {
            drawHSeparator(i * gridHeight / NRows);
        }
    }

    void step() override {
        float slotButtonWidth = box.size.x / NCols;
        float slotButtonHeight = box.size.y / NRows;
        for(int row = 0; row < NRows; ++row) {
            for(int col = 0; col < NCols; ++col) {
                slotButton[row][col]->box.pos = Vec(col * slotButtonWidth, row * slotButtonHeight);
                slotButton[row][col]->box.size.x = slotButtonWidth;
                slotButton[row][col]->box.size.y = slotButtonHeight;
            }
        }
        Widget::step();
    }
};

#endif
