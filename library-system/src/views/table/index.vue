<template>
  <div class="app-container">
    <form-panel ref="editPannel" />
    <div class="table-title">
      <span>Book Info List</span>
      <!--el-select v-model="searchKey" placeholder="请选择">
        <el-option v-for="item in options" :key="item.value" :label="item.label" :value="item.value" />
      </el-select>
      <el-input v-model="searchValue" placeholder="请输入内容" prefix-icon="el-icon-search" /-->
      <el-button class="add-button" type="primary" plain @click="handleAdd()">Add book</el-button>
    </div>
    <el-table v-loading="listLoading" :data="list.filter(data => !search || data.Name.toLowerCase().includes(search.toLowerCase())).slice((currentPage-1)*pagesize,currentPage*pagesize)" element-loading-text="Loading" border fit highlight-current-row @sort-change="handleSort">
      <el-table-column sortable="custom" label="Name" align="center">
        <template slot-scope="scope">
          <span><a :href="'/#/book/'+scope.row.id">{{ scope.row.Name }}</a></span>
        </template>
      </el-table-column>
      <el-table-column sortable="custom" label="Author" align="center">
        <template slot-scope="scope">
          <span>{{ scope.row.Author }}</span>
        </template>
      </el-table-column>
      <el-table-column sortable="custom" label="Price" align="center">
        <template slot-scope="scope">
          <span>{{ scope.row.Price }}</span>
        </template>
      </el-table-column>
      <el-table-column
        label="Type"
        align="center"
        :filters="typeFilter"
        :filter-method="filterType"
      >
        <template slot-scope="scope">
          <span>{{ scope.row.Type }}</span>
        </template>
      </el-table-column>
      <el-table-column align="center">
        <template slot="header" slot-scope="scope">
          <el-input
            v-model="search"
            size="mini"
            placeholder="输入关键字搜索"
            style="width:130px;"
          />
        </template>
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
        :total="booksCount"
        @current-change="handleCurrentChange"
      />
    </div>
  </div>
</template>

<script>
import {
  getBookList,
  deleteBook
} from '@/api/book'
import { getGroupList } from '@/api/group'
import Form from './Form'
export default {
  components: {
    'form-panel': Form
  },
  data() {
    return {
      currentPage: 1,
      pagesize: 5,
      booksCount: 5,
      search: '',
      list: [{
        id: '',
        Name: '',
        Author: '',
        Price: ''
      }],
      typeFilter: [],
      groupList: {},
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
        getBookList({ 'sort_by': event.column.label, 'order': this.orderFilter(event.order) }).then(response => {
          this.list = response.data.data
          this.listLoading = false
        })
      } else {
        getBookList().then(response => {
          this.list = response.data.data
          this.listLoading = false
        })
      }
    },
    fetchData() {
      this.listLoading = true
      getBookList({}).then(response => {
        this.list = response.data.data
        this.booksCount = response.data.data.length
        getGroupList().then(response => {
          const groupInfo = response.data
          groupInfo.forEach((obj, index) => {
            this.groupList[obj.id] = obj.name
            this.typeFilter.push({ 'text': obj.name, 'value': obj.name })
          })
          this.list.forEach((obj, index, step) => {
            this.list[index].Type = this.groupList[this.list[index].Type]
          })
          this.listLoading = false
        })
      })
    },
    handleEdit(scope) {
      this.$refs.editPannel.edit(scope.$index, scope.row)
    },
    handleDelete(index, id) {
      this.listLoading = true
      deleteBook(id).then(response => {
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
    },
    filterType(value, row) {
      return row.Type === value
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
