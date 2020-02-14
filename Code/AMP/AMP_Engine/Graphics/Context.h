// Copyright 2020 Simon Keller. All Rights Reserved.

#pragma once

#include <EGL/egl.h>
#include <android\native_window.h>
#include "stdio.h"
#include "cassert"

class Context
{
public:
	void initDisplay(ANativeWindow* window);
	void SwapBuffers();
	void termDisplay();
	int32_t getWidth();
	int32_t getHeight();

	EGLDisplay display = NULL;
private:
	EGLSurface surface;
	EGLContext context;
	int32_t width;
	int32_t height;
	ANativeWindow* window = nullptr;
};

