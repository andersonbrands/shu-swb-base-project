/***************************************************************************************
*	Title: WindowsPlatformTask.h
*	Author: Brandao, Anderson
*	Date: 2014
*
***************************************************************************************/

#ifndef WINDOWS_PLATFORM_TASK_H_
#define WINDOWS_PLATFORM_TASK_H_

#define D3D_DEBUG_INFO    // Enable debugging information, so the .NET environment can help you.

#include "../Framework/Platform/Platform.h"
#include "../Framework/Utilities/Singleton.h"
#include "../Framework/EventManager/EventHandler.h"
#include "../Framework/EventManager/EventManager.h"
#include <Windows.h>
#include <d3dx9.h>

using namespace Framework;

class WindowsPlatformTask : public Platform, public EventHandler, public Singleton<WindowsPlatformTask> {
    private:
        MSG msg_;

        LPDIRECT3D9             g_pD3D;
        LPDIRECT3DDEVICE9       g_pd3dDevice;

        WNDCLASSEX wc_;
        HWND hWnd_;

        D3DPRESENT_PARAMETERS d3dParams_;	//everything we need to setup D3D

        int lastWindowedWidth_, lastWindowedHeight_;	//remember the window size if we drop back from fullscreen
        int lastWindowedPositionX_, lastWindowedPositionY_;	//remember the window position if we drop back from fullscreen

        HRESULT setupD3D();

        bool isDeviceLost();
        void toggleFullScreen();

    public:
        WindowsPlatformTask(const unsigned int priority);
        virtual ~WindowsPlatformTask();

        static LRESULT CALLBACK InitialWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
            if (Msg == WM_NCCREATE) {
                LPCREATESTRUCT create_struct = reinterpret_cast<LPCREATESTRUCT>(lParam);
                void * lpCreateParam = create_struct->lpCreateParams;
                WindowsPlatformTask * this_window = reinterpret_cast<WindowsPlatformTask *>(lpCreateParam);
                SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this_window));
                SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&WindowsPlatformTask::StaticWndProc));
                return this_window->MsgProc(hWnd, Msg, wParam, lParam);
            }
            return DefWindowProc(hWnd, Msg, wParam, lParam);
        }

        static LRESULT CALLBACK StaticWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
            LONG_PTR user_data = GetWindowLongPtr(hWnd, GWLP_USERDATA);
            WindowsPlatformTask * this_window = reinterpret_cast<WindowsPlatformTask *>(user_data);
            return this_window->MsgProc(hWnd, Msg, wParam, lParam);
        }
        static LRESULT CALLBACK MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

        LPDIRECT3DDEVICE9 getDevice() {
            return g_pd3dDevice;
        };

        int getBufferWidth() const {
            return d3dParams_.BackBufferWidth;
        }
        int getBufferHeight() const {
            return d3dParams_.BackBufferHeight;
        }

        HINSTANCE getHInst() {
            return wc_.hInstance;
        }

        HWND getHWnd() {
            return hWnd_;
        }

        virtual bool	start();
        virtual void 	onSuspend();
        virtual void 	update();
        virtual void 	onResume();
        virtual void 	stop();

        virtual void handleEvent(Event* pEvent);
};

#endif // WINDOWS_PLATFORM_TASK_H_
