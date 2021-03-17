import request from '@/utils/request'
import { getToken } from '@/utils/auth'

export function getGroupList() {
  return request({
    url: '/group',
    method: 'get'
  })
}

export function getGroupDetail(groupId) {
  return request({
    url: `/group/${groupId}`,
    method: 'get'
  })
}

export function addGroup(data) {
  return request({
    url: '/group',
    method: 'post',
    headers: {
      'Authorization': `Bearer ${getToken()}`
    },
    data
  })
}

export function editGroup(id, data) {
  return request({
    url: `/group/${id}`,
    method: 'put',
    headers: {
      'Authorization': `Bearer ${getToken()}`
    },
    data
  })
}

export function deleteGroup(id) {
  return request({
    url: `/group/${id}`,
    method: 'delete',
    headers: {
      'Authorization': `Bearer ${getToken()}`
    }
  })
}

