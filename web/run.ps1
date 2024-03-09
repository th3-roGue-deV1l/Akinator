# Compile the C++ code to WebAssembly
emcc .\Techhi.cpp -o Techhi.js --preload-file .\serialized_data.txt `
    -s EXPORTED_FUNCTIONS="['_handleUserYesInputFromJS', '_handleUserNoInputFromJS', '_startGame', '_main']" `
    -s EXTRA_EXPORTED_RUNTIME_METHODS='["ccall", "UTF8ToString"]'

# Run the web server
npm run dev
