<template>
  <div>
    <div class="book-info">
      <el-upload
        class="avatar-uploader"
        action=""
        :show-file-list="false"
        :before-upload="beforeAvatarUpload"
      >
        <div v-if="info.coverUrl"><el-image :src="`/api/v1${info.coverUrl}`" :fit="fit" class="avatar" /></div>
        <i v-else class="el-icon-plus avatar-uploader-icon" />
      </el-upload>
      <ul>
        <li class="book-name">
          书名：{{ info.Name }}
        </li>
        <li>
          作者：{{ info.Author }}
        </li>
        <li>
          价格：{{ info.Price }}
        </li>
        <li>
          借阅状态：{{ getBorrowInfo() }}
        </li>
      </ul>
      <el-button class="borrow-button" type="primary" plain :disabled="borrowed" @click="getBorrowBook">借阅</el-button></div>
  </div>
</template>

<script>
import {
  getBookDetail,
  borrowBook,
  coverUpload
} from '@/api/book'
import { getToken } from '@/utils/auth'
export default {
  name: 'Detail',
  data() {
    return {
      info: {
        id: '',
        Name: '',
        Author: '',
        Price: '',
        coverUrl: ''
      },
      borrowed: false
    }
  },
  created() {
    this.fetchData()
  },
  methods: {
    fetchData() {
      getBookDetail(this.$route.params.bookId).then(response => {
        this.info = response.data.data
        if (this.info.owner) {
          this.borrowed = true
        }
      })
    },
    getBorrowInfo() {
      if (this.borrowed) {
        return `已被${this.info.owner}借走`
      }
      return '可借阅'
    },
    getBorrowBook() {
      borrowBook(this.$route.params.bookId).then(response => {
        this.fetchData()
        this.borrowed = true
      })
    },
    handleAvatarSuccess(res, file) {
      this.imageUrl = URL.createObjectURL(file.raw)
    },
    beforeAvatarUpload(file) {
      const isPNG = file.type === 'image/png'
      const isLt10M = file.size / 1024 / 1024 < 10
      let upload = true
      if (!isPNG) {
        this.$message.error('上传头像图片只能是 PNG 格式!')
        upload = false
      }
      if (!isLt10M) {
        this.$message.error('上传头像图片大小不能超过 10MB!')
        upload = false
      }
      if (upload) {
        const fd = new FormData()
        fd.append('cover', file)
        coverUpload(this.$route.params.bookId, fd).then(response => {
          this.fetchData()
        })
      }
      return false
    },
    getToken() {
      return getToken()
    }

  }
}
</script>

<style scoped>
.book-info{

  width: 500px;
  margin: 0 auto;
  font-size: 20px;
  line-height: 40px;
  margin-top: 50px;
  margin-bottom: 50px;
}
.borrow-button{
  margin-left: 80px;
}
</style>
<style>
  .avatar-uploader .el-upload {
    border: 1px dashed #d9d9d9;
    border-radius: 6px;
    cursor: pointer;
    position: relative;
    overflow: hidden;
  }
  .avatar-uploader .el-upload:hover {
    border-color: #409EFF;
  }
  .avatar-uploader-icon {
    font-size: 28px;
    color: #8c939d;
    width: 178px;
    height: 178px;
    line-height: 178px;
    text-align: center;
  }
  .avatar {
    width: 178px;
    display: block;
  }
</style>
