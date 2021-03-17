<template>
  <div>
    <el-dialog title="编辑面板" :visible.sync="editTableVisible">
      <el-form :model="editData" ref="information-form" inline>
        <el-form-item label="作品名" prop="name">
          <el-input
            type="text"
            v-model.trim="editData.name"
            placeholder="输入作品名"
          ></el-input>
        </el-form-item>
        <el-form-item label="作者名" prop="author">
          <el-input
            type="text"
            v-model.trim="editData.author"
            placeholder="输入作者名"
          ></el-input>
        </el-form-item>
        <el-form-item label="图片链接" prop="url">
          <el-input
            type="text"
            v-model.trim="editData.url"
            placeholder="输入链接名"
          ></el-input>
        </el-form-item>
        <el-form-item label="图片类别" prop="category">
          <el-input
            type="text"
            v-model.trim="editData.category"
            placeholder="输入图片类别"
          ></el-input>
        </el-form-item>
      </el-form>
      <el-button type="primary" @click="submitEditData">保 存</el-button>
      <el-button type="info" @click="editTableVisible = false">取 消</el-button>
    </el-dialog>
  </div>
</template>

<script>
import { editArtwork } from '@/api/artwork'

export default {
  data () {
    return {
      editData: "",
      editTableVisible: false,
      editRowIndex: null
    }
  },
  props: ['table'],
  methods: {
    edit: function (index, row) {
      var tmp_object = JSON.parse(JSON.stringify(row))
      this.editData = tmp_object
      this.editTableVisible = true
      this.editRowIndex = index
    },
    submitEditData: function () {
      let token = localStorage.getItem('token')
      // eslint-disable-next-line
      editArtwork(this.editData.id, this.editData, token).then(res => {
        this.editTableVisible = false
        this.$message.success('修改成功')
        this.table.splice(parseInt(this.editRowIndex), 1, JSON.parse(JSON.stringify(this.editData)))
        this.editRowIndex = null
      }).catch(error => {
        this.$message.error(Object.values(error.response.data.error_msg)[0])
      })
    }
  }
}
</script>