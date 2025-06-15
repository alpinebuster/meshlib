import createModule from './MRJavaScript.js';
import postWasmLoad from './post_load_mrjs.js';

// Define the various stages of embind loading and their weights.
const LOADING_STAGES = [
    {
        "id": "download",
        "name": "Resource Acquisition",
        "weight": 20,
        "description": "Download the WebAssembly module and related resources",
        "estimatedDuration": 1000
    },
    {
        "id": "wasm",
        "name": "WebAssembly Compilation",
        "weight": 25,
        "description": "Compile WebAssembly bytecode",
        "estimatedDuration": 800
    },
    {
        "id": "embind",
        "name": "Embind Initialization",
        "weight": 30,
        "description": "Build bindings from C++ to JavaScript",
        "estimatedDuration": 1200
    },
    {
        "id": "runtime",
        "name": "Runtime Preparation",
        "weight": 20,
        "description": "Initialize memory management and function mapping",
        "estimatedDuration": 600
    },
    {
        "id": "ready",
        "name": "Application Ready",
        "weight": 5,
        "description": "Complete final preparations",
        "estimatedDuration": 200
    }
];


class EmbindProgressTracker {
    constructor() {
        this.currentStageIndex = 0;
        this.currentStageProgress = 0;
        this.startTime = null;
        this.stageStartTime = null;
        this.isLoading = false;

        // DOM elements
        this.progressSection = document.getElementById('wasm-progress-section');
        this.progressFill = document.getElementById('wasm-progress-fill');
        this.progressText = document.getElementById('wasm-progress-text');
        this.statusDisplay = document.getElementById('wasm-status-display');
        this.logs = document.getElementById('logs');
        // this.logo = document.getElementById("logo");
        this.spinner = document.getElementById("spinner");

        // Initialize the reference to the stage element.
        this.stageElements = {};
        LOADING_STAGES.forEach(stage => {
            this.stageElements[stage.id] = document.getElementById(`stage-${stage.id}`);
        });
    }
    hideLoader() {
        this.progressFill.style.display = "none";
        this.progressText.style.display = "none";
        this.statusDisplay.style.display = "none";
        this.logs.style.display = "none";
        // this.logo.style.display = "none";
        this.spinner.style.display = "none";
        this.progressSection.style.display = "none";
    }
    startLoading() {
        this.isLoading = true;
        this.startTime = Date.now();
        this.currentStageIndex = 0;
        this.currentStageProgress = 0;
        this.resetUI();
        this.log('Start the Embind loading process.', 'success');
        this.updateStage(0);
    }
    updateStage(stageIndex, progress = 0) {
        if (stageIndex >= LOADING_STAGES.length) {
            this.completeLoading();
            return;
        }

        this.currentStageIndex = stageIndex;
        this.currentStageProgress = progress;
        this.stageStartTime = Date.now();

        const stage = LOADING_STAGES[stageIndex];

        Object.values(this.stageElements).forEach(el => {
            el.classList.remove('active', 'completed');
        });

        // Mark the previous stage as complete.
        for (let i = 0; i < stageIndex; i++) {
            const prevStage = LOADING_STAGES[i];
            this.stageElements[prevStage.id].classList.add('completed');
        }

        this.stageElements[stage.id].classList.add('active');
        this.statusDisplay.textContent = `${stage.name}: ${stage.description}`;
        this.log(`Enter stage: ${stage.name}`, 'info');

        this.updateProgress();
    }
    updateStageProgress(progress) {
        this.currentStageProgress = Math.min(100, Math.max(0, progress));
        this.updateProgress();
    }
    updateProgress() {
        let totalProgress = 0;

        // Calculate the progress of the completed stages.
        for (let i = 0; i < this.currentStageIndex; i++) {
            totalProgress += LOADING_STAGES[i].weight;
        }

        // Add the progress of the current stage.
        if (this.currentStageIndex < LOADING_STAGES.length) {
            const currentStage = LOADING_STAGES[this.currentStageIndex];
            totalProgress += (currentStage.weight * this.currentStageProgress) / 100;
        }

        // Update progress bar
        this.progressFill.style.width = `${totalProgress}%`;
        this.progressText.textContent = `${Math.round(totalProgress)}%`;

        // Estimate the remaining time.
        if (this.startTime && totalProgress > 0) {
            const elapsed = Date.now() - this.startTime;
            const estimatedTotal = (elapsed / totalProgress) * 100;
            const remaining = Math.max(0, estimatedTotal - elapsed);

            if (remaining > 1000) {
                this.log(`ETA: ${Math.round(remaining / 1000)}s`, 'info');
            }
        }
    }
    completeLoading() {
        this.isLoading = false;

        Object.values(this.stageElements).forEach(el => {
            el.classList.remove('active');
            el.classList.add('completed');
        });

        // Update the final status.
        this.progressFill.style.width = '100%';
        this.progressText.textContent = '100%';
        this.statusDisplay.textContent = 'Loading complete! The application is ready.';

        const totalTime = Date.now() - this.startTime;
        this.log(`Loading complete, total duration: ${totalTime}ms`, 'success');
    }
    resetUI() {
        this.progressFill.style.width = '0%';
        this.progressText.textContent = '0%';
        this.statusDisplay.textContent = 'Ready to start loading....';

        Object.values(this.stageElements).forEach(el => {
            el.classList.remove('active', 'completed');
        });
    }
    log(message, type = 'info') {
        const logEntry = document.createElement('div');
        logEntry.className = `log-entry ${type}`;
        logEntry.textContent = `[${new Date().toLocaleTimeString()}] ${message}`;
        this.logs.appendChild(logEntry);
        this.logs.scrollTop = this.logs.scrollHeight;
    }
    reset() {
        this.isLoading = false;
        this.currentStageIndex = 0;
        this.currentStageProgress = 0;
        this.startTime = null;
        this.stageStartTime = null;
        this.resetUI();
        this.logs.innerHTML = '';
        this.log('The system has been reset.', 'info');
    }
}


window.onerror = function (e) {
    Module.setStatus("Exception thrown, see JavaScript console");
    if (meshFileLoaderElement) meshFileLoaderElement.style.display = "none";
    spinnerElement.style.display = "none";
    statusElement.style.display = "none";
    Module.setStatus = function (e) {
        e && Module.printErr("[post-exception status] " + e);
    }
}

function createModuleConfiguration(progressTracker, meshFileLoaderElement, postWasmLoadHook) {
    return {
        preRun: [
            function () {
                progressTracker.log('Execute the pre-run hook.');
                progressTracker.updateStage(1);
            }
        ],
        postRun: [
            function () {
                progressTracker.log('Execute the post-run hook.');
                progressTracker.updateStage(4);
                setTimeout(() => {
                    progressTracker.completeLoading();
                }, 200);
            }
        ],
        // Intercept and enhance the embind status messages
        setStatus: function (text) {
            progressTracker.log(`Embind Status: ${text}`);

            // NOTE: Update different loading stages based on status text
            if (text.includes('Downloading') || text.includes('Loading')) {
                progressTracker.updateStage(0);

                // Attempt to parse the progress information.
                const progressMatch = text.match(/\((\d+)\/(\d+)\)/);
                if (progressMatch) {
                    const [, current, total] = progressMatch;
                    const progress = (parseInt(current) / parseInt(total)) * 100;
                    progressTracker.updateStageProgress(progress);
                }
            } else if (text.includes('Compiling') || text.includes('Instantiating')) {
                progressTracker.updateStage(1);
            } else if (text.includes('Running') || text.includes('Initializing')) {
                progressTracker.updateStage(3);
            } else if (text === '') {
                // An empty status usually indicates completion
                progressTracker.updateStage(4);
            }
        },
        onRuntimeInitialized: function () {
            progressTracker.log('Runtime initialization complete.', 'success');
            progressTracker.hideLoader();

            if (meshFileLoaderElement) {
                meshFileLoaderElement.style.display = "block";
            }

            if (typeof postWasmLoadHook === 'function') {
                postWasmLoadHook();
            }
        },
        onAbort: function (reason) {
            progressTracker.log(`Loading aborted: ${reason}`, 'error');
            progressTracker.statusDisplay.textContent = 'Loading failed.';
        },

        totalDependencies: 0,
        monitorRunDependencies: function (remaining) {
            this.totalDependencies = Math.max(this.totalDependencies, remaining);
            const completed = this.totalDependencies - remaining;
            const statusText = remaining ? 
                `Preparing... (${completed}/${this.totalDependencies})` : 
                "All downloads complete.";
            this.setStatus(statusText);
        },
        print: function () {
            const outputElement = document.getElementById("output");

            if (outputElement) {
                outputElement.value = "";
            }
            
            // Return the actual print function
            return function (message) {
                // Dealing with the situation of multiple parameters
                if (arguments.length > 1) {
                    message = Array.prototype.slice.call(arguments).join(" ");
                }

                console.log(message);

                if (outputElement) {
                    outputElement.value += message + "\n";
                    outputElement.scrollTop = outputElement.scrollHeight;
                }
            }
        }(),
    };
}

export async function initializeWasmModule(options = {}) {
    const progressTracker = new EmbindProgressTracker();

    let logoElement = document.getElementById("logo");
    let spinnerElement = document.getElementById("spinner");
    let meshFileLoaderElement = document.getElementById('meshFileLoader');

    const {
        postWasmLoadHook = () => console.log('Running postWasmLoadHook!!!'),
        onProgress = null,
        onError = null
    } = options;

    const postWasmLH_ = () => {
        postWasmLoad();
        postWasmLoadHook();
    }

    try {
        // Set the initial state
        progressTracker.updateStage(0);
        progressTracker.log('Starting WASM module initialization...');

        const moduleConfig = createModuleConfiguration(
            progressTracker, 
            meshFileLoaderElement, 
            postWasmLoadHook=postWasmLH_,
        );

        // If custom progress callbacks are provided, integrate them into the configuration
        if (onProgress) {
            const originalSetStatus = moduleConfig.setStatus;
            moduleConfig.setStatus = function(text) {
                originalSetStatus.call(this, text);
                onProgress(text, progressTracker.currentStage);
            };
        }
        moduleConfig.setStatus("Downloading...");

        // NOTE: Call the factory function of the Emscripten module and pass in the configuration
        const Module = await createModule(moduleConfig);
        
        progressTracker.log('WASM module successfully initialized', 'success');
    
        return Module;
    } catch (error) {
        const errorMessage = `Failed to initialize WASM module: ${error.message}`;
        progressTracker.log(errorMessage, 'error');

        if (meshFileLoaderElement) meshFileLoaderElement.style.display = "none";
        spinnerElement.style.display = "none";
        moduleConfig.setStatus = function (e) {
            e && moduleConfig.printErr("[post-exception status] " + e);
        }

        if (onError) {
            onError(error);
        } else {
            throw error;
        }
    }
}

export function loadWasmModule() {
    return initializeWasmModule();
}
