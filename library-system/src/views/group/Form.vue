<template>
  <el-dialog :title="title" :visible.sync="dialogVisible">
    <el-form ref="groupInfo" :model="groupInfo" label-width="80px">
      <el-form-item label="name">
        <el-input v-model="groupInfo.name" />
      </el-form-item>
      <el-form-item label="Type">
        <el-input v-model="groupInfo.Type" />
      </el-form-item>
    </el-form>
    <el-button @click="handleSubmit(switcher, 'groupInfo')">Submit</el-button>
  </el-dialog>
</template>

<script>
import { addGroup, editGroup } from '@/api/group'
export default {
  data: function() {
    return {
      title: '',
      dialogVisible: false,
      switcher: '',
      groupIndex: '',
      groupInfo: {
        name: '',
        Type: ''
      }
    }
  },
  methods: {
    edit(index, data) {
      this.title = 'Edit book'
      this.switcher = 'edit'
      this.groupIndex = index
      this.groupInfo = Object.assign({}, data)
      this.dialogVisible = true
    },
    add() {
      this.groupInfo = {}
      this.switcher = 'add'
      this.title = 'Add book'
      this.dialogVisible = true
    },
    handleSubmit(switcher, groupInfo) {
      this.$refs[groupInfo].validate(valid => {
        if (valid) {
          if (switcher === 'add') {
            addGroup(this.groupInfo)
              .then(response => {
                this.$parent.list.push(response.data)
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
            editGroup(this.groupInfo.id, this.groupInfo)
              .then(response => {
                this.$parent.list.splice(this.groupIndex, 1, this.groupInfo)
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

