function Config() {
	const name = 'three-meshsdk-editor';

	const userLanguage = navigator.language.split( '-' )[ 0 ];

	const suggestedLanguage = [ 'fr', 'ja', 'zh', 'ko', 'fa' ].includes( userLanguage ) ? userLanguage : 'en';

	const storage = {
		'language': suggestedLanguage,

		'autosave': true,

		'project/title': '',
		'project/editable': false,
		'project/vr': false,

		'project/renderer/antialias': true,
		'project/renderer/shadows': true,
		'project/renderer/shadowType': 1, // PCF
		'project/renderer/toneMapping': 0, // NoToneMapping
		'project/renderer/toneMappingExposure': 1,

		'settings/history': false,

		'settings/shortcuts/translate': 'w',
		'settings/shortcuts/rotate': 'e',
		'settings/shortcuts/scale': 'r',
		'settings/shortcuts/undo': 'z',
		'settings/shortcuts/focus': 'f'
	};

	if ( window.localStorage[ name ] === undefined ) {
		window.localStorage[ name ] = JSON.stringify( storage );
	} else {
		const data = JSON.parse( window.localStorage[ name ] );

		for ( const key in data ) {
			storage[ key ] = data[ key ];
		}
	}

	return {
		getKey: function ( key ) {
			return storage[ key ];
		},

		/**
		 * The `arguments` object is used to iterate through all the parameters passed to the function during the function call. In each iteration:
		 *
		 *	1. `arguments[i]` retrieves the current parameter, which is treated as the `key`.
		 *	2. `arguments[i + 1]` retrieves the next parameter, which is treated as the `value`.
		 */
		setKey: function () { // key, value, key, value ...
			for ( let i = 0, l = arguments.length; i < l; i += 2 ) {
				storage[ arguments[ i ] ] = arguments[ i + 1 ];
			}

			window.localStorage[ name ] = JSON.stringify( storage );

			console.log( '[' + /\d\d\:\d\d\:\d\d/.exec( new Date() )[ 0 ] + ']', 'Saved config to LocalStorage.' );
		},

		clear: function () {
			delete window.localStorage[ name ];
		}
	};
}

export { Config };
