import axios from 'axios'
import { getCookie } from '@/utils/cookies'
const service = axios.create({
  baseURL: 'api/', // api的base_url
  timeout: 5000 // request timeout
})
service.interceptors.request.use(function(config) {
  const csrftoken = getCookie('csrftoken')
  if (csrftoken !== null) {
    config.headers['X-CSRFToken'] = getCookie('csrftoken')
  }
  return config
})

export default service
