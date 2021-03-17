import Vue from 'vue'
import Router from 'vue-router'
import index from '@/pages/index'
import catagery from '@/pages/catagery'
import details from '@/pages/details'
import show from '@/pages/show'
import login from '@/pages/admin/login'
// import { Message } from 'element-ui'

Vue.use(Router)


const router = new Router({
    routes: [
        {
            path: '/',
            name: 'home',
            component: index
        },

        {
            path: '/catagery',
            name: 'catagery',
            component: catagery
        },

        {
          path: '/login',
          name: 'login',
          component: login
        },


        {
          path: '/details',
          name: 'details',
          component: details
        },

        {
            path: '/show',
            name: 'show',
            component: show
          }

    ]
})

router.beforeEach((to, from, next) => {
    let token = localStorage.getItem('token')

    if (!token || token == null) {
        if(to.name == 'admin'){
            next({
                name: 'login',
                query: {
                    'redirectTo': to.path,
                    'error' : 1
                }
            })
        }
        next()
    }else{
        if(to.name === 'login' || to.name === 'register'){
            next({
                name: 'home'
            })
        }
        next()
    }

})

export default router
