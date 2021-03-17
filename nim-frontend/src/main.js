import { createApp } from 'vue'
import axios from 'axios'
import ElementPlus from 'element-plus'
import 'element-plus/lib/theme-chalk/index.css'
import App from './App.vue'
import router from './router'
import store from './store'
import '@/permission'

const app = createApp(App)
app.use(router, axios)
app.use(ElementPlus)
app.use(store)
app.mount('#app')
