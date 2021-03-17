<template>
  <el-dialog :title="title" :visible.sync="dialogVisible">
    <el-form ref="bookInfo" :rules="rules" :model="bookInfo" label-width="80px">
      <el-form-item label="Name">
        <el-input v-model="bookInfo.Name" />
      </el-form-item>
      <el-form-item label="Author">
        <el-input v-model="bookInfo.Author" />
      </el-form-item>
      <el-form-item label="Type">
        <template>
          <el-select v-model="bookInfo.Type" placeholder="请选择">
            <el-option
              v-for="item in typeOptions"
              :key="item.id"
              :label="item.name"
              :value="item.id"
            />
          </el-select>
        </template>
      </el-form-item>
      <el-form-item label="Price">
        <el-input v-model.number="bookInfo.Price" type="number" />
      </el-form-item>
    </el-form>
    <el-button @click="handleSubmit(switcher, 'bookInfo')">Submit</el-button>
  </el-dialog>
</template>

<script>
import { addBook, editBook } from '@/api/book'
import { getGroupList } from '@/api/group'
export default {
  data: function() {
    return {
      title: '',
      dialogVisible: false,
      switcher: '',
      bookIndex: '',
      typeOptions: {},
      groupList: [],
      bookInfo: {
        Author: '',
        Name: '',
        Type: '',
        Price: 0
      },
      rules: {
        Name: [
          {
            required: true,
            message: '请输入名称',
            trigger: 'blur'
          },
          {
            min: 3,
            max: 5,
            message: '长度在 3 到 5 个字符',
            trigger: 'blur'
          }
        ]
      }
    }
  },
  created() {
    this.getTypeOption()
  },
  methods: {
    getTypeOption() {
      getGroupList().then(response => {
        this.typeOptions = response.data
      })
    },
    edit(index, data) {
      this.title = 'Edit book'
      this.switcher = 'edit'
      this.bookIndex = index
      this.bookInfo = Object.assign({}, data)
      this.dialogVisible = true
    },
    add() {
      this.bookInfo = {}
      this.switcher = 'add'
      this.title = 'Add book'
      this.dialogVisible = true
    },
    handleSubmit(switcher, bookInfo) {
      this.$refs[bookInfo].validate(valid => {
        if (valid) {
          if (switcher === 'add') {
            addBook(this.bookInfo)
              .then(response => {
                this.$parent.list.push(response.data.data)
                this.dialogVisible = false
                this.$message({
                  type: 'success',
                  message: 'Add completed'
                })
              })
              .catch(() => {
                this.$message({
                  type: 'error',
                  message: 'Add failed'
                })
              })
          }
          if (switcher === 'edit') {
            editBook(this.bookInfo.id, this.bookInfo)
              .then(response => {
                this.$parent.list.splice(this.bookIndex, 1, this.bookInfo)
                this.dialogVisible = false
                this.$message({
                  type: 'success',
                  message: 'Edit completed'
                })
              })
              .catch(() => {
                this.$message({
                  type: 'error',
                  message: 'Edit failed'
                })
              })
          }
        } else {
          return false
        }
      })
    }
  }
}
</script>

