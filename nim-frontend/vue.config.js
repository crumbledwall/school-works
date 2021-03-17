/** @type import('@vue/cli-service').ProjectOptions */
const fs = require('fs-extra')

module.exports = {
  // https://github.com/neutrinojs/webpack-chain/tree/v4#getting-started
  chainWebpack(config) {
    config.devtool('source-map')
  },
  publicPath: '/',
    devServer: {
      host: "0.0.0.0",
      port: 8080,
      overlay: {
          warnings: false,
          errors: true
      },
      https: true,
      disableHostCheck: true,
      key: fs.readFileSync('./cert/key.pem'),
      cert: fs.readFileSync('./cert/cert.pem'),
      proxy: {
        '^/api': {
          target: 'http://localhost:5000/',
          changeOrigin: true
        }
      }
  }
}
