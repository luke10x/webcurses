import path from "path";
import { fileURLToPath } from "url";
const __dirname = path.dirname(fileURLToPath(import.meta.url));

export default  {
    entry: './src/webcurses-terminal.js',
    output: {
        path: path.resolve(__dirname, './dist'),
        filename: 'webcurses-terminal-bundle.js',
        libraryTarget: 'var',
        library: 'webcurses_terminal'
    },
    experiments: { outputModule: true, },
    plugins: [
       //empty pluggins array
    ],
    module: {
         // https://webpack.js.org/loaders/babel-loader/#root
        rules: [
            {
                test: /\.css$/,
                use: [
                    'style-loader', // Adds CSS to the DOM by injecting a <style> tag
                    'css-loader',   // Interprets @import and url() like import/require() and will resolve them
                    'raw-loader',   // Required to run CSS into variable as text
                ],
                include: '/node_modules/',
            },
            {
                test: /.m?js$/,
                loader: 'babel-loader',
                exclude: /node_modules/,
            }
        ],
    },
    devtool: 'source-map'
}