<template>
  <div class="app-container">
    <form-panel ref="editPannel" />
    <div class="table-title">
      <span>Book Info List</span>
      <el-button class="add-button" type="primary" plain @click="handleAdd()">Add Group</el-button>
    </div>
    <el-table v-loading="listLoading" :data="list" border fit highlight-current-row>
      <el-table-column sortable="custom" label="name" align="center">
        <template slot-scope="scope">
          <span>{{ scope.row.name }}</span>
        </template>
      </el-table-column>
      <el-table-column align="center" label="operation">
        <template slot-scope="scope">
          <el-button size="mini" @click="handleEdit(scope)">Edit</el-button>
          <el-button size="mini" type="primary" plain @click="handleDelete(scope.$index, scope.row.id)">Delete</el-button>
        </template>
      </el-table-column>
    </el-table>
    <div style="text-align: center;margin-top: 30px;">
      <el-pagination
        background
        :current-page="currentPage"
        :page-size="pagesize"
        layout="prev, pager, next"
        :total="groupCount"
        @current-change="handleCurrentChange"
      />
    </div>
  </div>
</template>

<script>
import {
  getGroupList,
  deleteGroup
} from '@/api/group'
import Form from './Form'
export default {
  components: {
    'form-panel': Form
  },
  data() {
    return {
      currentPage: 1,
      pagesize: 5,
      groupCount: 5,
      search: '',
      list: [{
        id: '',
        name: ''//
        // books: ''
      }],
      listLoading: true
    }
  },
  created() {
    this.fetchData()
  },
  methods: {
    handleCurrentChange: function(currentPage) {
      this.currentPage = currentPage
    },
    handleSort(event) {
      this.listLoading = true
      if (event.order) {
        getGroupList({}).then(response => {
          this.list = response.data
          this.listLoading = false
        })
      } else {
        getGroupList().then(response => {
          this.list = response.data
          this.listLoading = false
        })
      }
    },
    fetchData() {
      this.listLoading = true
      getGroupList({}).then(response => {
        this.list = response.data
        this.groupCount = response.data.length
        this.listLoading = false
      })
    },
    handleEdit(scope) {
      this.$refs.editPannel.edit(scope.$index, scope.row)
    },
    handleDelete(index, id) {
      this.listLoading = true
      deleteGroup(id).then(response => {
        this.list.splice(index, 1)
        this.listLoading = false
        this.$message({
          type: 'success',
          message: 'Delete completed'
        })
      }).catch(() => {
        this.listLoading = false
      })
    },
    handleAdd() {
      this.$refs.editPannel.add()
    },
    orderFilter(order) {
      return order.replace('ending', '')
    }
  }
}
</script>

<style scoped>
.add-button {
    float: right;
}

.table-title {
    width: 100%;
    height: 50px;
    margin-right: 20px;
}
.el-input--prefix{
  width: 200px;
}
.el-input{
  margin-left: 20px
}
.el-select{
  margin-left: 20px
}
</style>
