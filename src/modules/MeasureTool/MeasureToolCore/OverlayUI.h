#pragma once

#include "D2DState.h"
#include "ToolState.h"

#include <common/display/monitors.h>
#include <common/utils/serialized.h>

class OverlayUIState final
{
    template<typename StateT, typename TickFuncT>
    OverlayUIState(StateT& toolState,
                   TickFuncT tickFunc,
                   const CommonState& commonState,
                   HWND window);

    ScreenSize _monitorArea;
    HWND _window = {};
    const CommonState& _commonState;
    D2DState _d2dState;
    std::function<void()> _tickFunc;
    std::thread _uiThread;
    bool _cursorOnScreen = true;

    template<typename ToolT, typename TickFuncT>
    static std::unique_ptr<OverlayUIState> CreateInternal(ToolT& toolState,
                                                          TickFuncT tickFunc,
                                                          const CommonState& commonState,
                                                          const wchar_t* toolWindowClassName,
                                                          void* windowParam,
                                                          const MonitorInfo& monitor);

public:
    OverlayUIState(OverlayUIState&&) noexcept = default;
    ~OverlayUIState() noexcept;

    static std::unique_ptr<OverlayUIState> Create(BoundsToolState& toolState,
                                                  const CommonState& commonState,
                                                  const MonitorInfo& monitor);
    static std::unique_ptr<OverlayUIState> Create(Serialized<MeasureToolState>& toolState,
                                                  const CommonState& commonState,
                                                  const MonitorInfo& monitor);
    inline HWND overlayWindowHandle() const
    {
        return _window;
    }

    void RunUILoop();
};