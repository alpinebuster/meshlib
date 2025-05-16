var postWasmLoad = function () {
    setTimeout(registerResize);
    setupColorTheme();
    updateCalculateMouseEvent();
    registerErrorHandling();

    Module.ccall('printtt', 'void', [], []);
};
