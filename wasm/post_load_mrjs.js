var postWasmLoad = function () {
    registerErrorHandling();

    // ccall
    Module.ccall('printtt', 'void', [], []);
    // function
    console.log('lerp result: ' + Module.lerp(1, 2, 0.5));
    // class
    var instance = new Module.MyClass(10, "hello");
    instance.incrementX();
    console.log("instance.x: ", instance.x);                                           // 11
    instance.x  = 20;                                                              // 20
    console.log("class_hello: ", Module.MyClass.getStringFromInstance(instance));  // "hello"
    instance.delete();


    // Vector
    var testV3f   = new Module.Vector3F(1.3, 43.2, 43.2);
    var testV3f_2 = new Module.Vector3F(2.3, 41.2, 3.2);
    console.log('testV3f length: ', testV3f.length());
    console.log('test_anglef: ', Module.angleF(testV3f, testV3f_2));


    // Color
    const color1 = new Module.Color(255, 0, 0);  // Red
    const color2 = new Module.Color(0, 255, 0);  // Green
    // Get the color component
    console.log("Color 1 - R:", color1.r, "G:", color1.g, "B:", color1.b, "A:", color1.a);
    console.log("Color 2 - R:", color2.r, "G:", color2.g, "B:", color2.b, "A:", color2.a);
    console.log("Color 1 Red Component:", color1.get(0));    // Obtain the red component
    console.log("Color 1 Green Component:", color1.get(1));  // Obtain the green component
                                                             // Set the color component
    color1.set(1, 128);
    console.log("Updated Color 1 - G:", color1.g);  // 128 should be output
                                                    // Create colors using the static factory function
    const whiteColor = Module.Color.white();
    console.log("White Color - R:", whiteColor.r, "G:", whiteColor.g, "B:", whiteColor.b, "A:", whiteColor.a);
    // Call other methods
    const colorUInt32 = color1.getUInt32();
    console.log("Color 1 as UInt32:", colorUInt32);
    const scaledAlpha = color1.scaledAlpha();
    console.log("Color 1 Scaled Alpha:", scaledAlpha);


    // `*Id` (e.g.EdgeId)
    const edge1 = new Module.EdgeId();
    const eid   = new Module.EdgeId(3);                                  // default
    const edge2 = new Module.EdgeId(42);
    const eid3  = Module.EdgeId.fromUndirected(new Module.UndirectedEdgeId(21));
    console.log("edge1.get(): ", edge1.get());                           // -1
    console.log("edge1.equals(): ", edge1.equals(eid));                  // false
    console.log("eid.lessThan(): ", eid.lessThan(edge2));                // true
    console.log("eid.get(): ", eid.get());                               // 3
    console.log("eid.valid(): ", eid.valid());                           // true
    console.log("eid.sym(): ", eid.sym().toInt());                       // 2
    console.log("eid.undirected().toInt(): ", eid.undirected().toInt())  // 1
    console.log("eid.even(): ", eid.even());                             // false
    console.log("eid.sym().even(): ", eid.sym().even());                 // true
    console.log("eid3.valid(): ", eid3.valid());                         // true
    console.log("edge1.valid(): ", edge1.valid());                       // false
    console.log("edge2.valid(): ", edge2.valid());                       // true

    let eobj = new Module.FaceId(2);
    let x    = eobj.toInt();
    console.log("x: ", x);  // 2
};
