import { Command } from '../Command.js';
import { ObjectLoader } from 'three';

class AddObjectCommand extends Command {
	/**
	 * @param {Editor} editor
	 * @param {THREE.Object3D|null} [object=null]
	 * @param {any|null} [wasmObject=null]
	 * @constructor
	 */
	constructor( editor, object=null, parent=null, index=null, wasmObject=null ) {
		super( editor );

		this.type = 'AddObjectCommand';

		this.object = object;
		this.parent = parent;
		this.index = index;
		this.wasmObject = wasmObject;

		if ( object !== null ) {
			this.name = editor.strings.getKey( 'command/AddObject' ) + ': ' + object.name;
		}
	}

	execute() {
		this.editor.addObject( this.object, this.parent, this.index );
		if (this.wasmObject) this.editor.addWasmObject( this.object.uuid, this.wasmObject );
		this.editor.select( this.object );
	}

	undo() {
		this.editor.removeObject( this.object );
		this.editor.deselect();
	}

	toJSON() {
		const output = super.toJSON( this );

		output.object = this.object.toJSON();

		return output;
	}

	fromJSON( json ) {
		super.fromJSON( json );

		this.object = this.editor.objectByUuid( json.object.object.uuid );

		if ( this.object === undefined ) {
			const loader = new ObjectLoader();
			this.object = loader.parse( json.object );
		}
	}
}

export { AddObjectCommand };
