
import router from './router'
import store from './store'

import { getToken } from '@/utils/auth' // get token from cookie

const whiteList = ['/login', '/register'] // no redirect whitelist

router.beforeEach(async(to, from, next) => {
  // determine whether the user has logged in
  const hasToken = getToken()

  if (hasToken) {
    if (to.path === '/login') {
      // if is logged in, redirect to the home page
      next({ path: '/' })
    } else {
      const hasGetUserInfo = store.getters.token
      if (hasGetUserInfo) {
        next()
      } else {
        // remove token and go to login page to re-login
        await store.dispatch('user/resetToken')
        next(`/login?redirect=${to.path}`)
      }
    }
  } else {
    /* has no token*/

    if (whiteList.indexOf(to.path) !== -1) {
      // in the free login whitelist, go directly
      next()
    } else {
      // other pages that do not have permission to access are redirected to the login page.
      next(`/login?redirect=${to.path}`)
    }
  }
})

