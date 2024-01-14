'use strict';

import xtermCss from 'raw-loader!xterm/css/xterm.css';
import { Terminal } from 'xterm';
import { FitAddon } from 'xterm-addon-fit';

window.emscriptenPrograms = {};
window.terminals = {};
window.pressedKeys = {};

class WebcursesTerminal extends HTMLElement {
    constructor() {
        super();
        this.terminal = new Terminal();
        this.fitAddon = new FitAddon();
        this.terminal.loadAddon(this.fitAddon);

        // Use Shadow DOM to encapsulate styles
        this.attachShadow({ mode: 'open' });

    	  this.pressedKeys = []

        // const program = this.getAttribute('program');
        // console.log({program});
		// window.Module = {
		//   preRun: [() => {
		// 	ENV.TERM = 'xterm';
		// 	FS.init(
		// 	  () => {
		// 		if (this.pressedKeys.length > 0) {
		// 		  const first = this.pressedKeys.shift()
		// 		  return first ;
		// 		}
		// 		return null;
		// 	  }, 
		// 	  (input) => {
		// 		this.terminal.write(new Uint8Array([input]))
		// 	  },
		// 	  null
		// 	);
		//   }],
		//   postRun: [function() {}],
		//   printErr: (stderr) => console.error('STDERRPIPE:', stderr)
		// };
	}

    connectedCallback() {
        const program = this.getAttribute('program');
        console.log({program});
        
        fetch(program)
            .then(resp => resp.text())
            .then(text => {
				        console.log({text})
                
                this.shadowRoot.innerHTML = `
					      <style>
                    ${xtermCss}

                    /* Add some basic styling */
                    .xterm {
                        height: 100%;
                        width: 100%;
                    }
                    .xterm.xterm-viewport {
                        background-color: yellow;
                    }
					      </style>
					      <div id="terminal" class="xterm"></div>
				        `;

                window.terminals[program] = this.terminal;
                window.pressedKeys[program] = this.pressedKeys;

                // Add loaded application JS (Emscripten output.js)
				        const script = document.createElement('script');
				        script.textContent = `
                window.emscriptenPrograms['${program}'] = function () {
                    const location = '${program}'.substring(0, '${program}'.lastIndexOf('/') + 1)

                    var Module = {
                        locateFile: (basename) => location + basename,
                        preRun: [() => {
                            ENV.TERM = 'xterm';
                            FS.init(
                                () => {
                                    if (window.pressedKeys['${program}'].length > 0) {
                                        const first = window.pressedKeys['${program}'].shift()
                                        return first ;
                                    }
                                    return null;
                                }, 
                                (input) => {
                                    window.terminals['${program}'].write(new Uint8Array([input]))
                                },
                                null
                            );
                        }],
                        postRun: [function() {}],
                        printErr: (stderr) => console.error('STDERRPIPE:', stderr)
                    };

                    // Emscripten code will use current module
                    // setting globals there.
                    // But we wrap it with isolation layer
                    ${text} ;;;

                    return Module;
                };

                // Execute the isolation layer
                window.emscriptenPrograms['${program}']();
                `;
                this.shadowRoot.appendChild(script);

                this.terminal.open(this.shadowRoot.getElementById('terminal'));
                this.fitAddon.fit();

                const viewportEl = this.shadowRoot.querySelector('.xterm-viewport');
                viewportEl.style.backgroundColor = 'transparent';

                const terminalEl = this.shadowRoot.querySelector('.xterm .terminal');
                terminalEl.style.display = 'flex';
                terminalEl.style.justifyContent = 'center';
                terminalEl.style.alignItems = 'center';
                viewportEl.style.backgroundColor = 'tranparent';

                const screenEl = this.shadowRoot.querySelector('.xterm-screen');
                screenEl.style.backgroundColor = '#222';

                this.terminal.onKey(e => {
                    const raw = new TextEncoder().encode(e.key)
                    const bytes = Array.from(raw);
                    this.pressedKeys.push(...bytes)
                });
            }); // End of on-fetch-then

        // Adjust terminal size on window resize
        window.addEventListener('resize', () => {
            this.fitAddon.fit();
        });
    }

   disconnectedCallback() {
       // Clean up when the element is removed from the document
       window.removeEventListener('resize', this.fitAddon.fit);
       this.terminal.dispose();
   }
}

customElements.define('webcurses-terminal', WebcursesTerminal);
