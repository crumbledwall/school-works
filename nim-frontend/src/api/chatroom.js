import request from '@/utils/request'

export function addRoom(data) {
  return request({
    url: '/api/v1/chatroom',
    method: 'post',
    data
  })
}

export function getRoom() {
  return request({
    url: '/api/v1/chatroom',
    method: 'get'
  })
}
