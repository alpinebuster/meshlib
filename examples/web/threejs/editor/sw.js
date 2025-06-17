const cacheName = 'three-meshlib-editor';

const assets = [
	'./',

	'./manifest.json',
	'./images/icon.png',

	'../files/favicon.ico',

	'../node_modules/three/build/three.module.js',

	'three/addons/controls/TransformControls.js',

	'three/addons/libs/chevrotain.module.min.js',
	'three/addons/libs/fflate.module.js',

	'three/addons/libs/draco/draco_decoder.js',
	'three/addons/libs/draco/draco_decoder.wasm',
	'three/addons/libs/draco/draco_encoder.js',
	'three/addons/libs/draco/draco_wasm_wrapper.js',

	'three/addons/libs/draco/gltf/draco_decoder.js',
	'three/addons/libs/draco/gltf/draco_decoder.wasm',
	'three/addons/libs/draco/gltf/draco_wasm_wrapper.js',

	'three/addons/libs/meshopt_decoder.module.js',

	'three/addons/libs/mikktspace.module.js',

	'three/addons/libs/motion-controllers.module.js',

	'three/addons/libs/rhino3dm/rhino3dm.wasm',
	'three/addons/libs/rhino3dm/rhino3dm.js',

	'three/addons/loaders/3DMLoader.js',
	'three/addons/loaders/3MFLoader.js',
	'three/addons/loaders/AMFLoader.js',
	'three/addons/loaders/ColladaLoader.js',
	'three/addons/loaders/DRACOLoader.js',
	'three/addons/loaders/FBXLoader.js',
	'three/addons/loaders/GLTFLoader.js',
	'three/addons/loaders/KMZLoader.js',
	'three/addons/loaders/KTX2Loader.js',
	'three/addons/loaders/MD2Loader.js',
	'three/addons/loaders/OBJLoader.js',
	'three/addons/loaders/MTLLoader.js',
	'three/addons/loaders/PCDLoader.js',
	'three/addons/loaders/PLYLoader.js',
	'three/addons/loaders/RGBELoader.js',
	'three/addons/loaders/STLLoader.js',
	'three/addons/loaders/SVGLoader.js',
	'three/addons/loaders/TGALoader.js',
	'three/addons/loaders/TDSLoader.js',
	'three/addons/loaders/USDZLoader.js',
	'three/addons/loaders/VOXLoader.js',
	'three/addons/loaders/VRMLLoader.js',
	'three/addons/loaders/VTKLoader.js',
	'three/addons/loaders/XYZLoader.js',

	'three/addons/curves/NURBSCurve.js',
	'three/addons/curves/NURBSUtils.js',

	'three/addons/interactive/HTMLMesh.js',
	'three/addons/interactive/InteractiveGroup.js',

	'three/addons/environments/RoomEnvironment.js',

	'three/addons/exporters/DRACOExporter.js',
	'three/addons/exporters/GLTFExporter.js',
	'three/addons/exporters/OBJExporter.js',
	'three/addons/exporters/PLYExporter.js',
	'three/addons/exporters/STLExporter.js',
	'three/addons/exporters/USDZExporter.js',

	'three/addons/helpers/VertexNormalsHelper.js',

	'three/addons/utils/BufferGeometryUtils.js',

	'three/addons/webxr/XRControllerModelFactory.js',

	'./images/rotate.svg',
	'./images/scale.svg',
	'./images/translate.svg',

	'./js/libs/codemirror/codemirror.css',
	'./js/libs/codemirror/theme/monokai.css',

	'./js/libs/codemirror/codemirror.js',
	'./js/libs/codemirror/mode/javascript.js',
	'./js/libs/codemirror/mode/glsl.js',

	'./js/libs/esprima.js',
	'./js/libs/jsonlint.js',

	'./js/libs/codemirror/addon/dialog.css',
	'./js/libs/codemirror/addon/show-hint.css',
	'./js/libs/codemirror/addon/tern.css',

	'./js/libs/codemirror/addon/dialog.js',
	'./js/libs/codemirror/addon/show-hint.js',
	'./js/libs/codemirror/addon/tern.js',
	'./js/libs/acorn/acorn.js',
	'./js/libs/acorn/acorn_loose.js',
	'./js/libs/acorn/walk.js',
	'./js/libs/ternjs/polyfill.js',
	'./js/libs/ternjs/signal.js',
	'./js/libs/ternjs/tern.js',
	'./js/libs/ternjs/def.js',
	'./js/libs/ternjs/comment.js',
	'./js/libs/ternjs/infer.js',
	'./js/libs/ternjs/doc_comment.js',
	'./js/libs/tern-threejs/threejs.js',

	'./js/libs/signals.min.js',
	'./js/libs/ui.js',
	'./js/libs/ui.three.js',

	'./js/libs/app.js',
	'./js/Player.js',
	'./js/Script.js',

	//

	'./css/main.css',

	'./js/EditorControls.js',
	'./js/Storage.js',

	'./js/Editor.js',
	'./js/Config.js',
	'./js/History.js',
	'./js/Loader.js',
	'./js/LoaderUtils.js',
	'./js/Menubar.js',
	'./js/Menubar.File.js',
	'./js/Menubar.Edit.js',
	'./js/Menubar.Add.js',
	'./js/Menubar.Help.js',
	'./js/Menubar.View.js',
	'./js/Menubar.Status.js',
	'./js/Resizer.js',
	'./js/Selector.js',
	'./js/Sidebar.js',
	'./js/Sidebar.Scene.js',
	'./js/Sidebar.Project.js',
	'./js/Sidebar.Project.Renderer.js',
	'./js/Sidebar.Project.Materials.js',
	'./js/Sidebar.Project.App.js',
	'./js/Sidebar.Project.Image.js',
	'./js/Sidebar.Project.Video.js',
	'./js/Sidebar.Settings.js',
	'./js/Sidebar.Settings.History.js',
	'./js/Sidebar.Settings.Shortcuts.js',
	'./js/Sidebar.Properties.js',
	'./js/Sidebar.Object.js',
	'./js/Sidebar.Object.Animation.js',
	'./js/Sidebar.Geometry.js',
	'./js/Sidebar.Geometry.BufferGeometry.js',
	'./js/Sidebar.Geometry.Modifiers.js',
	'./js/Sidebar.Geometry.BoxGeometry.js',
	'./js/Sidebar.Geometry.CapsuleGeometry.js',
	'./js/Sidebar.Geometry.CircleGeometry.js',
	'./js/Sidebar.Geometry.CylinderGeometry.js',
	'./js/Sidebar.Geometry.DodecahedronGeometry.js',
	'./js/Sidebar.Geometry.ExtrudeGeometry.js',
	'./js/Sidebar.Geometry.IcosahedronGeometry.js',
	'./js/Sidebar.Geometry.LatheGeometry.js',
	'./js/Sidebar.Geometry.OctahedronGeometry.js',
	'./js/Sidebar.Geometry.PlaneGeometry.js',
	'./js/Sidebar.Geometry.RingGeometry.js',
	'./js/Sidebar.Geometry.SphereGeometry.js',
	'./js/Sidebar.Geometry.ShapeGeometry.js',
	'./js/Sidebar.Geometry.TetrahedronGeometry.js',
	'./js/Sidebar.Geometry.TorusGeometry.js',
	'./js/Sidebar.Geometry.TorusKnotGeometry.js',
	'./js/Sidebar.Geometry.TubeGeometry.js',
	'./js/Sidebar.Material.js',
	'./js/Sidebar.Material.BooleanProperty.js',
	'./js/Sidebar.Material.ColorProperty.js',
	'./js/Sidebar.Material.ConstantProperty.js',
	'./js/Sidebar.Material.MapProperty.js',
	'./js/Sidebar.Material.NumberProperty.js',
	'./js/Sidebar.Material.Program.js',
	'./js/Sidebar.Script.js',
	'./js/Strings.js',
	'./js/Toolbar.js',
	'./js/Viewport.js',
	'./js/Viewport.Controls.js',
	'./js/Viewport.Info.js',
	'./js/Viewport.ViewHelper.js',
	'./js/Viewport.XR.js',

	'./js/Command.js',
	'./js/commands/AddObjectCommand.js',
	'./js/commands/RemoveObjectCommand.js',
	'./js/commands/MoveObjectCommand.js',
	'./js/commands/SetPositionCommand.js',
	'./js/commands/SetRotationCommand.js',
	'./js/commands/SetScaleCommand.js',
	'./js/commands/SetValueCommand.js',
	'./js/commands/SetUuidCommand.js',
	'./js/commands/SetColorCommand.js',
	'./js/commands/SetGeometryCommand.js',
	'./js/commands/SetGeometryValueCommand.js',
	'./js/commands/MultiCmdsCommand.js',
	'./js/commands/AddScriptCommand.js',
	'./js/commands/RemoveScriptCommand.js',
	'./js/commands/SetScriptValueCommand.js',
	'./js/commands/SetMaterialCommand.js',
	'./js/commands/SetMaterialColorCommand.js',
	'./js/commands/SetMaterialMapCommand.js',
	'./js/commands/SetMaterialValueCommand.js',
	'./js/commands/SetMaterialVectorCommand.js',
	'./js/commands/SetSceneCommand.js',
	'./js/commands/Commands.js',

	//

	'./examples/arkanoid.app.json',
	'./examples/camera.app.json',
	'./examples/particles.app.json',
	'./examples/pong.app.json',
	'./examples/shaders.app.json'

];

self.addEventListener( 'install', async function () {

	const cache = await caches.open( cacheName );

	assets.forEach( async function ( asset ) {

		try {

			await cache.add( asset );

		} catch {

			console.warn( '[SW] Couldn\'t cache:', asset );

		}

	} );

} );

self.addEventListener( 'fetch', async function ( event ) {

	const request = event.request;

	if ( request.url.startsWith( 'chrome-extension' ) ) return;

	event.respondWith( networkFirst( request ) );

} );

async function networkFirst( request ) {

	try {

		let response = await fetch( request );

		if ( request.url.endsWith( 'editor/' ) || request.url.endsWith( 'editor/index.html' ) ) { // copied from coi-serviceworker

			const newHeaders = new Headers( response.headers );
			newHeaders.set( 'Cross-Origin-Embedder-Policy', 'require-corp' );
			newHeaders.set( 'Cross-Origin-Opener-Policy', 'same-origin' );

			response = new Response( response.body, { status: response.status, statusText: response.statusText, headers: newHeaders } );

		}

		if ( request.method === 'GET' ) {

			const cache = await caches.open( cacheName );
			cache.put( request, response.clone() );

		}

		return response;

	} catch {

		const cachedResponse = await caches.match( request );

		if ( cachedResponse === undefined ) {

			console.warn( '[SW] Not cached:', request.url );

		}

		return cachedResponse;

	}

}
