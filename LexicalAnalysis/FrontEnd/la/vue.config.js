const {defineConfig} = require('@vue/cli-service')
module.exports = defineConfig({
    transpileDependencies: true,
    devServer: {
        proxy: {
            '/analysis': {
                target: 'http://xjfyt.top:8000/la/analysis',
                // 允许跨域
                changeOrigin: true,
                ws: true,
                pathRewrite: {
                    '^/analysis': ''
                }
            },
            '/random_text': {
                target: 'http://xjfyt.top:8000/la/random_text',
                // 允许跨域
                changeOrigin: true,
                ws: true,
                pathRewrite: {
                    '^/random_text': ''
                }
            }
        }
    },
    chainWebpack: (config) => {
        config.plugin('html').tap(args => {
                args[0].title = '词法分析'
                return args
            }
        )
    }
})
