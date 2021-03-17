import { login, register } from '@/api/token'
import { getToken, setToken, removeToken } from '@/utils/auth'
import Cookies from 'js-cookie'

const getDefaultState = () => {
  return {
    token: getToken(),
    account: ''
  }
}

const state = getDefaultState()

const mutations = {
  RESET_STATE: (state) => {
    Object.assign(state, getDefaultState())
  },
  SET_TOKEN: (state, token) => {
    state.token = token
  },
  SET_ACCOUNT: (state, account) => {
    state.account = account
  }
}

const actions = {
  // user login
  login({ commit }, userInfo) {
    const { email, password } = userInfo
    return new Promise((resolve, reject) => {
      login({ email: email.trim(), password: password }).then(response => {
        const { data } = response.data
        if (data.token) {
          commit('SET_TOKEN', data.token)
          commit('SET_ACCOUNT', data.account)
          Cookies.set('account', data.account)
          setToken(data.token)
        }
        resolve()
      }).catch(error => {
        console.log(error)
        reject(error)
      })
    })
  },

  register({ commit }, userInfo) {
    const { email, password } = userInfo
    return new Promise((resolve, reject) => {
      register({ email: email.trim(), password: password }).then(response => {
        const { info } = response.data
        if (info.token) {
          commit('SET_TOKEN', info.token)
          commit('SET_ACCOUNT', info.accid)
          Cookies.set('account', info.accid)
          setToken(info.token)
        }
        resolve()
      }).catch(error => {
        console.log(error)
        reject(error)
      })
    })
  },

  resetToken({ commit }) {
    return new Promise(resolve => {
      removeToken() // must remove  token  first
      commit('RESET_STATE')
      resolve()
    })
  }
}

export default {
  namespaced: true,
  state,
  mutations,
  actions
}
