var postWasmLoad = function () {
    registerErrorHandling();

    // ccall
    Module.ccall('printtt', 'void', [], []);
    
    // function
    console.log('lerp result: ' + Module.lerp(1, 2, 0.5));

    // class
    var instance = new Module.MyClass(10, "hello");
    instance.incrementX();
    instance.x; // 11
    instance.x = 20; // 20
    console.log("class_hello: ", Module.MyClass.getStringFromInstance(instance)); // "hello"
    instance.delete();

    var testV3f = new Module.Vector3f(1.3, 43.2, 43.2);
    console.log('testV3f length: ', testV3f.length());
};
