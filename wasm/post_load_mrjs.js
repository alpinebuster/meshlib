class MeshFileLoader {
    constructor() {
        this.fileInput = document.getElementById('file-input');
        this.dropZone = document.getElementById('file-drop-zone');
        this.progressContainer = document.getElementById('progress-container');
        this.progressFill = document.getElementById('progress-fill');
        this.statusMessage = document.getElementById('status-message');
        this.meshInfo = document.getElementById('mesh-info');
        this.infoGrid = document.getElementById('info-grid');

        this.initializeEventListeners();
    }

    initializeEventListeners() {
        // File input change event - this is the core functionality you asked about
        this.fileInput.addEventListener('change', (event) => {
            this.handleFileSelection(event.target.files);
        });

        // Drag and drop functionality for enhanced user experience
        this.dropZone.addEventListener('dragover', (event) => {
            event.preventDefault();
            this.dropZone.classList.add('dragover');
        });

        this.dropZone.addEventListener('dragleave', () => {
            this.dropZone.classList.remove('dragover');
        });

        this.dropZone.addEventListener('drop', (event) => {
            event.preventDefault();
            this.dropZone.classList.remove('dragover');
            this.handleFileSelection(event.dataTransfer.files);
        });

        // Click to open file dialog
        this.dropZone.addEventListener('click', () => {
            this.fileInput.click();
        });
    }

    async handleFileSelection(files) {
        if (!files || files.length === 0) {
            this.showStatus('No files selected', 'error');
            return;
        }

        // Process each file - this demonstrates handling multiple files
        for (let i = 0; i < files.length; i++) {
            const file = files[i];
            await this.processFile(file, i + 1, files.length);
        }
    }

    async processFile(file, currentIndex, totalFiles) {
        try {
            // Show loading state
            this.showStatus(`Processing file ${currentIndex} of ${totalFiles}: ${file.name}`, 'loading');
            this.showProgress(true);

            // Validate file type - important for security and user experience
            const fileExtension = this.getFileExtension(file.name);
            if (!this.isSupportedFormat(fileExtension)) {
                throw new Error(`Unsupported file format: ${fileExtension}`);
            }

            // Read file as ArrayBuffer - this is the key step for binary data
            const arrayBuffer = await this.readFileAsArrayBuffer(file);
            const uint8Array = new Uint8Array(arrayBuffer);

            // Simulate progress updates during processing
            this.updateProgress(30);

            // Call your WASM mesh loader - this is where your actual code would go
            const result = await Module.MeshLoad.fromBinaryData(uint8Array, fileExtension);

            this.updateProgress(80);

            if (result.success) {
                this.updateProgress(100);
                this.showStatus(`Successfully loaded ${file.name}`, 'success');
                this.displayMeshInfo(result.mesh, file.name);
            } else {
                throw new Error(result.error || 'Unknown error occurred');
            }

        } catch (error) {
            this.showStatus(`Error loading ${file.name}: ${error.message}`, 'error');
            console.error('Mesh loading error:', error);
        } finally {
            // Hide progress bar after a short delay
            setTimeout(() => {
                this.showProgress(false);
            }, 1000);
        }
    }

    // Helper method to read file as ArrayBuffer with progress tracking
    readFileAsArrayBuffer(file) {
        return new Promise((resolve, reject) => {
            const reader = new FileReader();

            reader.onprogress = (event) => {
                if (event.lengthComputable) {
                    const percentComplete = (event.loaded / event.total) * 30; // First 30% is file reading
                    this.updateProgress(percentComplete);
                }
            };

            reader.onload = (event) => {
                resolve(event.target.result);
            };

            reader.onerror = () => {
                reject(new Error('Failed to read file'));
            };

            reader.readAsArrayBuffer(file);
        });
    }

    getFileExtension(filename) {
        return filename.toLowerCase().split('.').pop();
    }

    isSupportedFormat(extension) {
        const supportedFormats = ['stl', 'obj', 'ply', 'off'];
        return supportedFormats.includes(extension);
    }

    showStatus(message, type) {
        this.statusMessage.textContent = message;
        this.statusMessage.className = `status-message status-${type}`;
        this.statusMessage.style.display = 'block';
    }

    showProgress(show) {
        this.progressContainer.style.display = show ? 'block' : 'none';
        if (!show) {
            this.updateProgress(0);
        }
    }

    updateProgress(percentage) {
        this.progressFill.style.width = `${percentage}%`;
    }

    displayMeshInfo(mesh, filename) {
        // Get mesh properties
        const vertexCount = mesh.getVertexCount();
        const faceCount = mesh.getFaceCount();
        const boundingBox = mesh.getBoundingBox();
        const volume = mesh.getVolume();
        const surfaceArea = "mesh.getSurfaceArea()";

        // Calculate derived properties
        const boxSize = {
            x: (boundingBox.max.x - boundingBox.min.x).toFixed(2),
            y: (boundingBox.max.y - boundingBox.min.y).toFixed(2),
            z: (boundingBox.max.z - boundingBox.min.z).toFixed(2)
        };

        // Build info display
        this.infoGrid.innerHTML = `
            <div class="info-item">
                <div class="info-label">Filename</div>
                <div class="info-value">${filename}</div>
            </div>
            <div class="info-item">
                <div class="info-label">Vertices</div>
                <div class="info-value">${vertexCount.toLocaleString()}</div>
            </div>
            <div class="info-item">
                <div class="info-label">Faces</div>
                <div class="info-value">${faceCount.toLocaleString()}</div>
            </div>
            <div class="info-item">
                <div class="info-label">Volume</div>
                <div class="info-value">${volume} units³</div>
            </div>
            <div class="info-item">
                <div class="info-label">Surface Area</div>
                <div class="info-value">${surfaceArea} units²</div>
            </div>
            <div class="info-item">
                <div class="info-label">Bounding Box Size</div>
                <div class="info-value">${boxSize.x} × ${boxSize.y} × ${boxSize.z}</div>
            </div>
        `;

        this.meshInfo.style.display = 'block';
    }
}

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
    instance.x = 20;                                                              // 20
    console.log("class_hello: ", Module.MyClass.getStringFromInstance(instance));  // "hello"
    instance.delete();


    // Vector
    var testV3f = new Module.Vector3F(1.3, 43.2, 43.2);
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
    const eid = new Module.EdgeId(3);                                  // default
    const edge2 = new Module.EdgeId(42);
    const eid3 = Module.EdgeId.fromUndirected(new Module.UndirectedEdgeId(21));
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
    let x = eobj.toInt();
    console.log("x: ", x);  // 2


    // Mesh
    // Load a mesh from binary data
    let mfl = new MeshFileLoader();
};
