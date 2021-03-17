import request from '@/utils/request'
import { getToken } from '@/utils/auth'

export function getBookList(params) {
  return request({
    url: '/book',
    method: 'get',
    params
  })
}

export function getBookDetail(bookId) {
  return request({
    url: `/book/${bookId}`,
    method: 'get'
  })
}

export function addBook(data) {
  return request({
    url: '/book',
    method: 'post',
    headers: {
      'Authorization': `Bearer ${getToken()}`
    },
    data
  })
}

export function editBook(id, data) {
  return request({
    url: `/book/${id}`,
    method: 'put',
    headers: {
      'Authorization': `Bearer ${getToken()}`
    },
    data
  })
}

export function deleteBook(id) {
  return request({
    url: `/book/${id}`,
    method: 'delete',
    headers: {
      'Authorization': `Bearer ${getToken()}`
    }
  })
}

export function borrowBook(id) {
  return request({
    url: `/book/borrow/${id}`,
    method: 'post',
    headers: {
      'Authorization': `Bearer ${getToken()}`
    }
  })
}

export function coverUpload(id, data) {
  return request({
    url: `/book/${id}/cover`,
    method: 'post',
    headers: {
      'Authorization': `Bearer ${getToken()}`,
      'Content-type': 'multipart/form-data;charset=UTF-8'
    },
    data
  })
}
