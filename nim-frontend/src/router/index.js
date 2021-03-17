import { createWebHistory, createRouter } from 'vue-router'
import Main from '@/pages/Main/index.vue'
import Login from '@/pages/Login/index.vue'
import Register from '@/pages/Register/index.vue'
import Single from '@/pages/Single/index.vue'

export const routes = [
  {
    path: '/',
    name: 'Home',
    component: Main
  },
  {
    path: '/login',
    name: 'Login',
    component: Login
  },
  {
    path: '/register',
    name: 'Register',
    component: Register
  },
  {
    path: '/single',
    name: 'single',
    component: Single
  }
]

export const asyncRoutes = []

const router = createRouter({
  history: createWebHistory(),
  routes
})

export default router
